#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Misc/ScopedSlowTask.h"
#include "Models/IWeastModel.h"

#if WITH_EDITOR

#include "Timer/WeastTimer.h"

#endif

class FWeastModel : public IWeastModel
{
public:
	FWeastModel();

	virtual ~FWeastModel() override;

public:

	virtual void BeginSession() override;
	virtual void EndSession() override;

public:
	//Overriden Function

	virtual TSharedPtr<FWeatherCityRoute> GetActiveCity() override;
	virtual bool SetNewActiveCity(FGuid& InActiveId) override;
	virtual TSharedPtr<FWeatherCityRoute> GetCityById(FGuid InId) const override;
	virtual const TSet<TSharedPtr<FWeatherCityRoute>>& GetAllCity() const override;
	virtual bool PinUnpinById(FGuid Id) const override;
	virtual void RefreshData() override;
	virtual FGuid GetActiveCityId() const override;
	virtual FOnActiveCityChangeMulticast& OnActiveCityChange() override;
	virtual FOnFinishedLoadingMulticast& OnFinishedLoading() override;
	virtual void PopulateDailiesOnActiveCity(TArray<TSharedPtr<FWeatherDailyInfo>>& OutDailies) override;
	virtual void PopulateHourlyOnActiveCity(TArray<TSharedPtr<FWeatherHourlyInfo>>& OutHourly) override;
	virtual bool HasFinishedLoading() const override;
	virtual float LoadingPercentage() const override;
private:
	//private Function

	//Populate the cities and then register route for HTTP request
	void RegisterRequest();

	//Add the request to HTTPRequest
	void RegisterRoute(FWeatherCityRoute& InCityRoute);

	//Add a city to the CurrentCity TMap
	void RegisterCity(TSharedPtr<FWeatherCityRoute> InCity);

	//Send the request to the API
	void InvokeApiCall();

	//Reset the data to default, used during EndSession
	void Reset();

	//Save Data to Config JSON
	void SaveConfigData();

	//Try populate CitiesRegistry Data 
	bool TryLoadCitiesFromJson();

	//Populate struct Current from API
	void PopulateStructCurrentFromAPIJsonObject(const TSharedPtr<FJsonObject> InResponseObj, FWeatherCurrentInfo& OutWeatherCurrentInfo);

	//Populate struct Hourly from API
	void PopulateStructHourlyFromAPIJsonObject(const TSharedPtr<FJsonObject> InResponseObj, TArray<FWeatherHourlyInfo>& OutWeatherHourlyInfo);

	//Populate struct Daily from API
	void PopulateStructDailyFromAPIJsonObject(const TSharedPtr<FJsonObject> InResponseObj, TArray<FWeatherDailyInfo>& OutWeatherDailyInfo);

	//Populate CitiesRegistry
	void PopulateCitiesFromConfigJsonObject(const TSharedPtr<FJsonObject> InCitiesObj);

	//Called when a response is given from the API
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FWeatherCityRoute* CurrentCity);

private:
	//Variable

	TSet<TSharedPtr<FWeatherCityRoute>> CitiesRegistry;

	FGuid ActiveCityID;

	TSet<FHttpRequestPtr> PendingRequests;

	FOnActiveCityChangeMulticast OnActiveCityChangeDelegate;

	FOnFinishedLoadingMulticast OnFinishedLoadingDelegate;

	int32 TotalRequest;

#if WITH_EDITOR

	FWeastTimer AutoRefreshTimer;

#endif

	static FString DefaultURL;

	static FString DefaultExcludeURL;

	static FString APIKey;

};
