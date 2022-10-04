#pragma once

#include "Common/WeastCommon.h"

#include "Settings/WeastSettings.h"
#include "IWeastModel.generated.h"

USTRUCT()
struct FWeather
{
	GENERATED_BODY()

public:
};

USTRUCT()
struct FWeatherIcon : public FWeather
{
	GENERATED_BODY()
public:

	FWeatherIcon()
		: id(0)
		, description(TEXT(""))
		, icon(TEXT(""))
	{

	}

	~FWeatherIcon() { }

public:
	UPROPERTY()
		int32 id;

	UPROPERTY()
		FString description;

	UPROPERTY()
		FString icon;
};
USTRUCT()
struct FWeatherDailyTempInfo : public FWeather
{
	GENERATED_BODY()
public:
	FWeatherDailyTempInfo()
		: max(0.f)
		, min(0.f)
	{
		
	}

	~FWeatherDailyTempInfo()
	{}
public:
	UPROPERTY()
		float max;
	UPROPERTY()
		float min;
};


USTRUCT()
struct FWeatherDailyInfo : public FWeather
{
	GENERATED_BODY()
public:
	FWeatherDailyInfo()
		: dt(0)
		, pop(0.f)
		, temp(FWeatherDailyTempInfo())
		, weather(FWeatherIcon())
		, DayAfterToday(0)
	{

	}

	~FWeatherDailyInfo()
	{}
public:
	UPROPERTY()
		int32 dt;

	UPROPERTY()
		float pop;

	UPROPERTY()
		FWeatherDailyTempInfo temp;

	UPROPERTY()
		FWeatherIcon weather;

	int32 DayAfterToday;
};

USTRUCT()
struct FWeatherHourlyInfo : public FWeather
{
	GENERATED_BODY()
public:
	FWeatherHourlyInfo()
		: dt(0)
		, temp(0.f)
		, weather(FWeatherIcon())
	{

	}

	~FWeatherHourlyInfo()
	{}
public:
	UPROPERTY()
		int32 dt;

	UPROPERTY()
		float temp;

	UPROPERTY()
		FWeatherIcon weather;

	int32 Hour;
};

USTRUCT()
struct FWeatherCurrentInfo : public FWeather
{
	GENERATED_BODY()
public:
	FWeatherCurrentInfo()
		:dt(0)
		, sunrise(0)
		, sunset(0)
		, temp(0)
		, pressure(0)
		, humidity(0)
		, wind_speed(0)
		, weather(FWeatherIcon())
	{

	}

	~FWeatherCurrentInfo() { }
public:
	UPROPERTY()
		int32 dt;

	UPROPERTY()
		int64 sunrise;

	UPROPERTY()
		int64 sunset;

	UPROPERTY()
		int32 temp;

	UPROPERTY()
		float pressure;

	UPROPERTY()
		int32 humidity;

	UPROPERTY()
		float wind_speed;

	UPROPERTY()
		FWeatherIcon weather;
};

USTRUCT()
struct FWeatherCityRoute
{
	GENERATED_BODY()
public:
	FWeatherCityRoute()
		: City(TEXT(""))
		, Region(TEXT(""))
		, Country(TEXT(""))
		, IsPinned(false)
		, timezone_offset(0)
		, Latitude(0)
		, Longitude(0)
		, IsDefault(false)
		, Id(FGuid())
		, current(FWeatherCurrentInfo())
		, daily(TArray<FWeatherDailyInfo>())
		, hourly(TArray<FWeatherHourlyInfo>())


	{
		//daily.SetNum(8);
	}

	bool operator==(const FWeatherCityRoute& OtherCity)
	{
		return Id == OtherCity.Id;
	}

	bool operator==(const FWeatherCityRoute& OtherCity) const
	{
		return Id == OtherCity.Id;
	}

	friend uint32 GetTypeHash(const FWeatherCityRoute& InOther)
	{
		return GetTypeHash(InOther.Id);
	}

	FText GetSunset() const
	{
		if (current.sunset != 0)
		{
			const FDateTime Date = FDateTime::FromUnixTimestamp(current.sunset) + FDateTime::FromUnixTimestamp(timezone_offset);
			const FString Hour = FString::FromInt(Date.GetHour12());
			const FString Minute = FString::FromInt(Date.GetMinute());
			const FString Unit = Date.GetHour() >= 12 ? TEXT("PM") : TEXT("AM");
			const FString CompleteHour = FString::Printf(TEXT("%s:%s %s"), *Hour, *Minute, *Unit);
			return FText::FromString(CompleteHour);
		}
		return FText();
	}

	FText GetSunrise() const
	{
		if (current.sunrise != 0)
		{
			const FDateTime Date = FDateTime::FromUnixTimestamp(current.sunrise) + FDateTime::FromUnixTimestamp(timezone_offset);
			const FString Hour = FString::FromInt(Date.GetHour12());
			const FString Minute = FString::FromInt(Date.GetMinute());
			const FString Unit = Date.GetHour() >= 12 ? TEXT("PM") : TEXT("AM");
			const FString CompleteHour = FString::Printf(TEXT("%s:%s %s"), *Hour, *Minute, *Unit);
			return FText::FromString(CompleteHour);
		}
		return FText();
	}

	int32 GetPressure() const
	{
		return current.pressure;
	}

	//Get Probability based on the day you want 0 == today, max = 7
	float GetPrecipitationProbabilityByDay(int32 InDay = 0) const
	{
		const int32 Day = FMath::Clamp<int32>(InDay, 0, 7);
		if(daily.Num())
		{
			return daily[Day].pop * 100.f;
		}
		return 0.f;
	}

	FText GetDay(int32 InDay = 0) const
	{
		const int32 Day = FMath::Clamp<int32>(InDay, 0, 7);
		if (daily.Num())
		{
			const EDayOfWeek DayOfWeek = (FDateTime::FromUnixTimestamp(daily[Day].dt)).GetDayOfWeek();
			return FText::FromString(GetDayAsString(DayOfWeek));
		}
		return FText();
	}

	FText GetHour(int32 InHour = 0) const
	{
		if (hourly.Num())
		{
			const FDateTime Date = FDateTime::FromUnixTimestamp(hourly[InHour].dt) + FDateTime::FromUnixTimestamp(timezone_offset);
			const FString Hour = FString::FromInt(Date.GetHour12());
			const FString Unit = Date.GetHour() >= 12 ? TEXT("PM") : TEXT("AM");
			const FString CompleteHour = FString::Printf(TEXT("%s%s"), *Hour, *Unit);
			return FText::FromString(CompleteHour);
		}
		return FText();
	}

	int32 GetMaxDailyTemp(int32 InDay = 0) const
	{
		const int32 Day = FMath::Clamp<int32>(InDay, 0, 7);
		if (daily.Num())
		{
			return daily[Day].temp.max;
		}
		return -1;
	}

	int32 GetHourlyTemp(int32 InHour = 0) const
	{
		if (hourly.Num())
		{
			return hourly[InHour].temp;
		}
		return -1;
	}

	int32 GetMinDailyTemp(int32 InDay = 0) const
	{
		const int32 Day = FMath::Clamp<int32>(InDay, 0, 7);
		if (daily.Num())
		{
			return daily[Day].temp.min;
		}
		return -1;
	}

	int32 GetWindSpeed() const
	{
		return current.wind_speed;
	}

	const int32& GetTemperature() const
	{
		return current.temp;
	}

	const FString& GetDescription() const
	{
		return current.weather.description;
	}

	void SetFullCityName()
	{
		FullCityName = FString(City + "," + Region + "," + Country);
	}

	void AddDaily(FWeatherDailyInfo InDaily)
	{
		daily.Add(InDaily);
	}

private:
	FString GetDayAsString(EDayOfWeek InDay) const
	{
		FString DayAsString = TEXT("Sunday");
		switch (InDay)
		{
			case EDayOfWeek::Monday:
				DayAsString = TEXT("Monday");
				break;
			case EDayOfWeek::Tuesday:
				DayAsString = TEXT("Tuesday");
				break;
			case EDayOfWeek::Wednesday:
				DayAsString = TEXT("Wednesday");
				break;
			case EDayOfWeek::Thursday:
				DayAsString = TEXT("Thursday");
				break;
			case EDayOfWeek::Friday:
				DayAsString = TEXT("Friday");
				break;
			case EDayOfWeek::Saturday:
				DayAsString = TEXT("Saturday");
				break;
			case EDayOfWeek::Sunday:
			default: ;
		}
		return DayAsString;
	}

public:
	UPROPERTY()
		FString City;

	UPROPERTY()
		FString Region;

	UPROPERTY()
		FString Country;

	FString FullCityName;

	UPROPERTY()
		bool IsPinned;

	UPROPERTY()
		int64 timezone_offset;

	UPROPERTY()
		float Latitude;

	UPROPERTY()
		float Longitude;

	UPROPERTY()
		bool IsDefault;

	UPROPERTY()
		FGuid Id;

	UPROPERTY()
		FWeatherCurrentInfo current;

	UPROPERTY()
		TArray<FWeatherDailyInfo> daily;

	UPROPERTY()
		TArray<FWeatherHourlyInfo> hourly;
};

using IWeastModelPtr = TSharedPtr<class IWeastModel>;

using IWeastModelRef = TSharedRef<class IWeastModel>;

DECLARE_MULTICAST_DELEGATE(FOnActiveCityChangeMulticast)
DECLARE_MULTICAST_DELEGATE(FOnFinishedLoadingMulticast)

class IWeastModel
{
public:
	virtual ~IWeastModel() { }

public:
	virtual void BeginSession() = 0;

	virtual void EndSession() = 0;

	virtual TSharedPtr<FWeatherCityRoute> GetActiveCity() = 0;

	virtual bool SetNewActiveCity(FGuid& NewPinnedGuid) = 0;

	virtual TSharedPtr<FWeatherCityRoute> GetCityById(FGuid Id) const = 0;

	virtual bool PinUnpinById(FGuid Id) const = 0;

	virtual const TSet<TSharedPtr<FWeatherCityRoute>>& GetAllCity() const = 0;

	virtual void RefreshData() = 0;

	virtual FGuid GetActiveCityId() const = 0;

	virtual FOnActiveCityChangeMulticast& OnActiveCityChange() = 0;

	virtual FOnFinishedLoadingMulticast& OnFinishedLoading() = 0;

	virtual void PopulateDailiesOnActiveCity(TArray<TSharedPtr<FWeatherDailyInfo>>& OutDailies) = 0;

	virtual void PopulateHourlyOnActiveCity(TArray<TSharedPtr<FWeatherHourlyInfo>>& OutHourly) = 0;

	virtual bool HasFinishedLoading() const = 0;

	virtual float LoadingPercentage() const = 0;
};
