
#include "WeastModel.h"

#include "HttpManager.h"
#include "ISettingsCategory.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "Backends/JsonStructDeserializerBackend.h"
#include "JsonObjectConverter.h"
#include "Logging/MessageLog.h"
#include "MessageLog/Public/MessageLogModule.h"
#include "Serialization/JsonSerializer.h"
#include "StructDeserializer.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "Misc/ScopedSlowTask.h"
#include "Serialization/Formatters/JsonArchiveInputFormatter.h"
#include "Serialization/Formatters/JsonArchiveOutputFormatter.h"

#define LOCTEXT_NAMESPACE "FWeastModel"

FString FWeastModel::DefaultURL = TEXT("https://api.openweathermap.org/data/3.0/onecall?lat={0}&lon={1}&units={2}&exclude={3}&appid={4}");
FString FWeastModel::DefaultExcludeURL = TEXT("alerts,minutely");
FString FWeastModel::APIKey = TEXT("98fb5333b3dfd5e1753831ea72b300e8");

FWeastModel::FWeastModel()
{
	TotalRequest = 0;

#if WITH_EDITOR

	AutoRefreshTimer = FWeastTimer();

#endif

}

FWeastModel::~FWeastModel()
{
	Reset();
}

void FWeastModel::BeginSession()
{
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");

	if (!MessageLogModule.IsRegisteredLogListing(WeastConstant::MSG_LOG_NAME))
	{
		MessageLogModule.RegisterLogListing(WeastConstant::MSG_LOG_NAME, LOCTEXT("WeastLabel", "Weast"));
	}

	FMessageLog(WeastConstant::MSG_LOG_NAME).NewPage(FText::Format(LOCTEXT("WeastMessageLogPageLabel", "Detailed Weast changes from {0}"), FText::AsTime(FDateTime::UtcNow())));

	FMessageLog(WeastConstant::MSG_LOG_NAME).Info(FText::Format(LOCTEXT("SessionBeginLabel", "Session began at {0}"), FText::AsTime(FDateTime::UtcNow())));

	MessageLogModule.OpenMessageLog(WeastConstant::MSG_LOG_NAME);

	if (!TryLoadCitiesFromJson())
	{
		FMessageLog(WeastConstant::MSG_LOG_NAME).CriticalError(LOCTEXT("LoadingError", "Couldn't load json DefaultCities file"));
	}
	//PopulateCities();

#if WITH_EDITOR

	if(const UWeastSettings* WeastSettings = GetDefault<UWeastSettings>())
	{
		if(WeastSettings->GetAutoRefresh())
		{
			AutoRefreshTimer.SetIsTickable(true);
			const float Minutes = WeastSettings->GetRefreshFrequency();
			const FTimespan MinutesTimespan = FTimespan::FromMinutes(Minutes);
			//Testing
			//const FTimespan MinutesTimespan = FTimespan::FromSeconds(Minutes);
			AutoRefreshTimer.SetThreshold(MinutesTimespan);
			FOnWeastTimerTick AutoRefreshFunction;
			AutoRefreshFunction.BindRaw(this, &FWeastModel::RefreshData);
			AutoRefreshTimer.ListenOnWeastTimerTick(AutoRefreshFunction);
		}
	}

#endif

	RegisterRequest();

	RefreshData();
}

void FWeastModel::EndSession()
{
	SaveConfigData();

	Reset();

	FMessageLog(WeastConstant::MSG_LOG_NAME).Info(FText::Format(LOCTEXT("SessionEndLabel", "Session ended at {0}"), FText::AsTime(FDateTime::UtcNow())));
}

TSharedPtr<FWeatherCityRoute> FWeastModel::GetActiveCity()
{
	for (TSharedPtr<FWeatherCityRoute, ESPMode::ThreadSafe>& WeatherCityRoute : CitiesRegistry)
	{
		if (ActiveCityID.IsValid())
		{
			if (WeatherCityRoute.IsValid() && WeatherCityRoute.Get()->Id == ActiveCityID)
			{
				return WeatherCityRoute;
			}
		}
	}
	return TSharedPtr<FWeatherCityRoute>();
}

bool FWeastModel::SetNewActiveCity(FGuid& InActiveId)
{
	for (TSharedPtr<FWeatherCityRoute, ESPMode::ThreadSafe>& WeatherCityRoute : CitiesRegistry)
	{
		if (WeatherCityRoute.IsValid() && WeatherCityRoute.Get()->Id == InActiveId)
		{
			WeatherCityRoute->IsPinned = true;
			ActiveCityID = InActiveId;
			if (OnActiveCityChangeDelegate.IsBound())
			{
				OnActiveCityChangeDelegate.Broadcast();
			}
			return true;
		}
	}
	return false;
}

TSharedPtr<FWeatherCityRoute> FWeastModel::GetCityById(FGuid InId) const
{
	for (TSharedPtr<FWeatherCityRoute, ESPMode::ThreadSafe> WeatherCityRoute : CitiesRegistry)
	{
		if (WeatherCityRoute.IsValid() && WeatherCityRoute.Get()->Id == InId)
		{
			return WeatherCityRoute;
		}
	}
	return TSharedPtr<FWeatherCityRoute>();
}

const TSet<TSharedPtr<FWeatherCityRoute>>& FWeastModel::GetAllCity() const
{
	return CitiesRegistry;
}

bool FWeastModel::PinUnpinById(FGuid Id) const
{
	if (const TSharedPtr<FWeatherCityRoute> CityToPin = GetCityById(Id))
	{
		if(CityToPin->Id == ActiveCityID)
		{
			return false;
		}
		CityToPin->IsPinned = !CityToPin->IsPinned;
		return true;
	}
	return false;
}

void FWeastModel::RefreshData()
{
	if(TotalRequest != 0)
	{
		return;
	}
	TotalRequest = CitiesRegistry.Num();
	InvokeApiCall();
	//FHttpModule::Get().GetHttpManager().Flush(EHttpFlushReason::FullFlush);
}

FGuid FWeastModel::GetActiveCityId() const
{
	return ActiveCityID;
}

FOnActiveCityChangeMulticast& FWeastModel::OnActiveCityChange()
{
	return OnActiveCityChangeDelegate;
}

FOnFinishedLoadingMulticast& FWeastModel::OnFinishedLoading()
{
	return OnFinishedLoadingDelegate;
}

void FWeastModel::PopulateDailiesOnActiveCity(TArray<TSharedPtr<FWeatherDailyInfo>>& OutDailies)
{
	OutDailies.Empty();
	for (TSharedPtr<FWeatherCityRoute, ESPMode::ThreadSafe>& WeatherCityRoute : CitiesRegistry)
	{
		if (ActiveCityID.IsValid())
		{
			if (WeatherCityRoute.IsValid() && WeatherCityRoute.Get()->Id == ActiveCityID)
			{
				for (int32 WeatherIndex = 0; WeatherIndex < WeatherCityRoute->daily.Num(); WeatherIndex++)
				{
					OutDailies.Add(MakeShareable(new FWeatherDailyInfo(WeatherCityRoute->daily[WeatherIndex])));
				}
			}
		}
	}
}

void FWeastModel::PopulateHourlyOnActiveCity(TArray<TSharedPtr<FWeatherHourlyInfo>>& OutHourly)
{
	OutHourly.Empty();
	for (TSharedPtr<FWeatherCityRoute, ESPMode::ThreadSafe>& WeatherCityRoute : CitiesRegistry)
	{
		if (ActiveCityID.IsValid())
		{
			if (WeatherCityRoute.IsValid() && WeatherCityRoute.Get()->Id == ActiveCityID)
			{
				const int32 DayForecast = WeatherCityRoute->hourly.Num() * 0.5f;
				for (int32 HourlyIndex = 0; HourlyIndex < DayForecast; HourlyIndex++)
				{
					OutHourly.Add(MakeShareable(new FWeatherHourlyInfo(WeatherCityRoute->hourly[HourlyIndex])));
				}
			}
		}
	}
}

bool FWeastModel::HasFinishedLoading() const
{
	return TotalRequest == 0;
}

float FWeastModel::LoadingPercentage() const
{
	return 1.f - (static_cast<float>(TotalRequest) /  static_cast<float>(CitiesRegistry.Num()));
}

void FWeastModel::RegisterRequest()
{
	for (TSharedPtr<FWeatherCityRoute, ESPMode::ThreadSafe>& City : CitiesRegistry)
	{
		RegisterRoute(*City.Get());
	}
}

void FWeastModel::RegisterRoute(FWeatherCityRoute& InCityRoute)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindRaw(this, &FWeastModel::OnResponseReceived, &InCityRoute);

	FStringFormatOrderedArguments StringFormatArguments;
	StringFormatArguments.Add(FStringFormatArg(InCityRoute.Latitude));
	StringFormatArguments.Add(FStringFormatArg(InCityRoute.Longitude));
	FString UnitFormat = TEXT("metric");
	if (const UWeastSettings* WeastSettings = GetDefault<UWeastSettings>())
	{
		UnitFormat = ETemperature::Helper::FieldValueBasedOnTemperature(WeastSettings->GetTemperatureUnit());
	}
	StringFormatArguments.Add(FStringFormatArg(UnitFormat));
	StringFormatArguments.Add(FStringFormatArg(DefaultExcludeURL));
	StringFormatArguments.Add(FStringFormatArg(APIKey));
	const FString NewURL = FString::Format(*DefaultURL, StringFormatArguments);

	FMessageLog(WeastConstant::MSG_LOG_NAME).Info(FText::Format(LOCTEXT("Error", "CurrentURL {0}"), FText::FromString(NewURL)));

	Request->SetURL(NewURL);
	Request->SetVerb("GET");
	PendingRequests.Add(Request);
}

void FWeastModel::RegisterCity(TSharedPtr<FWeatherCityRoute> InCity)
{
	if (InCity.IsValid())
	{
		CitiesRegistry.Add(InCity);
	}
}

void FWeastModel::InvokeApiCall()
{
	FMessageLog(WeastConstant::MSG_LOG_NAME).Info(FText::Format(LOCTEXT("ApiInvoke", "API Invoked At: {0}"), FText::AsDateTime(FDateTime::Now())));
	for (TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request : PendingRequests)
	{
		Request->ProcessRequest();
	}
}

void FWeastModel::Reset()
{
	PendingRequests.Empty();
	CitiesRegistry.Empty();
	ActiveCityID = FGuid();

#if WITH_EDITOR

	AutoRefreshTimer.Reset();

#endif
}

void FWeastModel::SaveConfigData()
{
	if (IPluginManager::Get().FindPlugin("Weast").IsValid())
	{
		const FString Path = IPluginManager::Get().FindPlugin("Weast")->GetBaseDir() / TEXT("Config/DefaultCities.Json");
		TArray<TSharedPtr<FJsonValue>> CitiesArray;

		for (TSharedPtr<FWeatherCityRoute, ESPMode::ThreadSafe>& WeatherCityRoute : CitiesRegistry)
		{
			const TSharedPtr< FJsonObject > CurrentCity = MakeShareable(new FJsonObject);
			CurrentCity->SetStringField("City", WeatherCityRoute->City);
			CurrentCity->SetStringField("Region", WeatherCityRoute->Region);
			CurrentCity->SetStringField("Country", WeatherCityRoute->Country);
			CurrentCity->SetNumberField("Latitude", WeatherCityRoute->Latitude);
			CurrentCity->SetNumberField("Longitude", WeatherCityRoute->Longitude);
			CurrentCity->SetStringField("ID", WeatherCityRoute->Id.ToString());
			CurrentCity->SetBoolField("IsDefault", WeatherCityRoute->Id == ActiveCityID);
			CurrentCity->SetBoolField("IsPinned", WeatherCityRoute->IsPinned);

			CitiesArray.Add(MakeShareable(new FJsonValueObject(CurrentCity)));
		}

		const TSharedRef<FJsonObject> JsonRootObject = MakeShareable(new FJsonObject);
		JsonRootObject->SetArrayField(WeastConstant::WEATHER_CITIES_ARRAY_FIELD, CitiesArray);
		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonRootObject, Writer);

		FFileHelper::SaveStringToFile(OutputString, *Path);
	}
}

bool FWeastModel::TryLoadCitiesFromJson()
{
	if (IPluginManager::Get().FindPlugin("Weast").IsValid())
	{
		FString JsonCities;
		const FString Path = IPluginManager::Get().FindPlugin("Weast")->GetBaseDir() / TEXT("Config/DefaultCities.Json");
		FFileHelper::LoadFileToString(JsonCities, *Path);
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonCities);
		TSharedPtr<FJsonObject> CitiesObj;
		FJsonSerializer::Deserialize(JsonReader, CitiesObj);
		PopulateCitiesFromConfigJsonObject(CitiesObj);
		return true;
	}

	return false;
}

void FWeastModel::PopulateStructCurrentFromAPIJsonObject(const TSharedPtr<FJsonObject> InResponseObj, FWeatherCurrentInfo& OutWeatherCurrentInfo)
{
	if (!InResponseObj.IsValid())
	{
		return;
	}
	const TSharedPtr<FJsonObject>* Current;
	if (InResponseObj->TryGetObjectField(WeastConstant::WEATHER_API_CURRENT_FIELD, Current))
	{
		if (!FJsonObjectConverter::JsonObjectToUStruct(Current->ToSharedRef(), FWeatherCurrentInfo::StaticStruct(), &OutWeatherCurrentInfo))
		{
			FMessageLog(WeastConstant::MSG_LOG_NAME).Error(LOCTEXT("ErrorConverting", "Error in converting Json to FWeatherInfo USTRUCT"));
		}
		const TArray<TSharedPtr<FJsonValue>>* WeatherArr;
		if((*Current)->TryGetArrayField(WeastConstant::WEATHER_API_WEATHER_FIELD, WeatherArr))
		{
			const TSharedPtr<FJsonObject>* Weather;
			if((*WeatherArr)[0]->TryGetObject(Weather))
			{
				if (!FJsonObjectConverter::JsonObjectToUStruct(Weather->ToSharedRef(), FWeatherIcon::StaticStruct(), &OutWeatherCurrentInfo.weather))
				{
					FMessageLog(WeastConstant::MSG_LOG_NAME).Error(LOCTEXT("ErrorConverting", "Error in converting Json to FWeatherIcon USTRUCT"));
				}
			}
			else
			{
				FMessageLog(WeastConstant::MSG_LOG_NAME).Error(LOCTEXT("ErrorConverting", "Error in getting ARRAY Object"));
			}
		}
	}
}

void FWeastModel::PopulateStructHourlyFromAPIJsonObject(const TSharedPtr<FJsonObject> InResponseObj,
	TArray<FWeatherHourlyInfo>& OutWeatherHourlyInfo)
{
	if (!InResponseObj.IsValid())
	{
		return;
	}
	bool IsRefresh = false;
	if (OutWeatherHourlyInfo.Num() > 0)
	{
		IsRefresh = true;
	}
	const TArray<TSharedPtr<FJsonValue>>* Current;
	if (InResponseObj->TryGetArrayField(WeastConstant::WEATHER_API_HOURLY_FIELD, Current))
	{
		for (int32 Index = 0; Index < Current->Num(); Index++)
		{
			TSharedPtr<FJsonValue> JsonValue = (*Current)[Index];
			const TSharedPtr<FJsonObject>* HourlyObj;
			if (JsonValue->TryGetObject(HourlyObj))
			{
				FWeatherHourlyInfo* HourlyInfo = new FWeatherHourlyInfo();
				if (FJsonObjectConverter::JsonObjectToUStruct(HourlyObj->ToSharedRef(), FWeatherHourlyInfo::StaticStruct(), HourlyInfo))
				{
					//problem
					HourlyInfo->Hour = Index;
					if (IsRefresh)
						OutWeatherHourlyInfo[Index] = *HourlyInfo;
					else
						OutWeatherHourlyInfo.Add(*HourlyInfo);

				}

				const TArray<TSharedPtr<FJsonValue>>* WeatherHourlyArr;
				if (HourlyObj->Get()->TryGetArrayField(WeastConstant::WEATHER_API_WEATHER_FIELD, WeatherHourlyArr))
				{
					const TSharedPtr<FJsonObject>* WeatherHourlyObj;
					if ((*WeatherHourlyArr)[0]->TryGetObject(WeatherHourlyObj))
					{
						FJsonObjectConverter::JsonObjectToUStruct(WeatherHourlyObj->ToSharedRef(), FWeatherIcon::StaticStruct(), &HourlyInfo->weather);
					}
				}
			}
		}
	}
}

void FWeastModel::PopulateStructDailyFromAPIJsonObject(const TSharedPtr<FJsonObject> InResponseObj,
                                                       TArray<FWeatherDailyInfo>& OutWeatherDailyInfo)
{
	if (!InResponseObj.IsValid())
	{
		return;
	}
	bool IsRefresh = false;
	if (OutWeatherDailyInfo.Num() > 0)
	{
		IsRefresh = true;
	}
	const TArray<TSharedPtr<FJsonValue>>* Current;
	if (InResponseObj->TryGetArrayField(WeastConstant::WEATHER_API_DAILY_FIELD, Current))
	{
		for (int32 Index = 0; Index < Current->Num() ; Index++)
		{
			TSharedPtr<FJsonValue> JsonValue = (*Current)[Index];
			const TSharedPtr<FJsonObject>* DailyObj;
			if (JsonValue->TryGetObject(DailyObj))
			{
				FWeatherDailyInfo* DailyInfo = new FWeatherDailyInfo();
				if (FJsonObjectConverter::JsonObjectToUStruct(DailyObj->ToSharedRef(), FWeatherDailyInfo::StaticStruct(), DailyInfo))
				{
					//problem 
					DailyInfo->DayAfterToday = Index;
					if (IsRefresh)
						OutWeatherDailyInfo[Index] = *DailyInfo;
					else
						OutWeatherDailyInfo.Add(*DailyInfo);
					//CityDailies.Add(MakeShareable(DailyInfo));
				}
				const TSharedPtr<FJsonObject>* TempObj;
				if(DailyObj->Get()->TryGetObjectField(WeastConstant::WEATHER_API_DAILY_TEMP_FIELD, TempObj))
				{
					FJsonObjectConverter::JsonObjectToUStruct(DailyObj->ToSharedRef(), FWeatherDailyTempInfo::StaticStruct(), &DailyInfo->temp);
				}
				const TArray<TSharedPtr<FJsonValue>>* WeatherDailyArr;
				if (DailyObj->Get()->TryGetArrayField(WeastConstant::WEATHER_API_WEATHER_FIELD, WeatherDailyArr))
				{
					const TSharedPtr<FJsonObject>* WeatherDailyObj;
					if ((*WeatherDailyArr)[0]->TryGetObject(WeatherDailyObj))
					{
						FJsonObjectConverter::JsonObjectToUStruct(WeatherDailyObj->ToSharedRef(), FWeatherIcon::StaticStruct(), &DailyInfo->weather);
					}
				}
			}
		}
	}
}

void FWeastModel::PopulateCitiesFromConfigJsonObject(const TSharedPtr<FJsonObject> InCitiesObj)
{
	if (!InCitiesObj.IsValid())
	{
		return;
	}
	const TArray<TSharedPtr<FJsonValue>>* Current;
	if (InCitiesObj->TryGetArrayField(WeastConstant::WEATHER_CITIES_ARRAY_FIELD, Current))
	{
		for (TSharedPtr<FJsonValue> JsonValue : *Current)
		{
			const TSharedPtr<FJsonObject>* JsonObj;
			if (JsonValue->TryGetObject(JsonObj))
			{
				FWeatherCityRoute* CityRoute = new FWeatherCityRoute();
				if (FJsonObjectConverter::JsonObjectToUStruct(JsonObj->ToSharedRef(), FWeatherCityRoute::StaticStruct(), CityRoute))
				{
					CityRoute->SetFullCityName();
					CitiesRegistry.Add(MakeShareable(CityRoute));
					if(CityRoute->IsDefault)
					{
						SetNewActiveCity(CityRoute->Id);
					}
				}
			}
		}
	}
}

void FWeastModel::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                     bool bConnectedSuccessfully, FWeatherCityRoute* CurrentCity)
{
	if (bConnectedSuccessfully)
	{
		TSharedPtr<FJsonObject> ResponseObj;
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		FJsonSerializer::Deserialize(Reader, ResponseObj);

		ResponseObj->TryGetNumberField("timezone_offset", CurrentCity->timezone_offset);

		PopulateStructCurrentFromAPIJsonObject(ResponseObj, CurrentCity->current);
		PopulateStructDailyFromAPIJsonObject(ResponseObj, CurrentCity->daily);
		PopulateStructHourlyFromAPIJsonObject(ResponseObj, CurrentCity->hourly);

	}
	else
	{
		FMessageLog(WeastConstant::MSG_LOG_NAME).Error(LOCTEXT("ErrorConnection", "Error calling API, try later"));
	}
	TotalRequest -= 1;
	if(HasFinishedLoading())
	{
		if (OnFinishedLoadingDelegate.IsBound())
		{
			OnFinishedLoadingDelegate.Broadcast();
		}
		if (OnActiveCityChangeDelegate.IsBound())
		{
			OnActiveCityChangeDelegate.Broadcast();
		}
	}
}


#undef LOCTEXT_NAMESPACE
