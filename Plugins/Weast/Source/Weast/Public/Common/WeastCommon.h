// Copyright (c) 2022 Maurious Paul Vincent. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "WeastCommon.generated.h"

namespace WeastConstant
{

    const FString WEATHER_URL_TOKYO = TEXT("https://api.openweathermap.org/data/3.0/onecall?lat=35.68&lon=139.75&exclude=alerts,minutely,hourly&appid=b6c959bbca4f0011acdf79b593d454aa");

    /// <summary>
	/// Holds the field string for response Json: current.
	/// </summary>
    const FString WEATHER_API_CURRENT_FIELD = TEXT("current");

    /// <summary>
	/// Holds the field string for response Json: weather.
	/// </summary>
    const FString WEATHER_API_WEATHER_FIELD = TEXT("weather");

    /// <summary>
	/// Holds the field string for response Json: daily.
	/// </summary>
    const FString WEATHER_API_DAILY_FIELD = TEXT("daily");

    /// <summary>
	/// Holds the field string for response Json: temp.
	/// </summary>
    const FString WEATHER_API_DAILY_TEMP_FIELD = TEXT("temp");

    /// <summary>
	/// Holds the field string for response Json: hourly.
	/// </summary>
    const FString WEATHER_API_HOURLY_FIELD = TEXT("hourly");

    /// <summary>
	/// Holds the field string for cities Json: Cities.
	/// </summary>
    const FString WEATHER_CITIES_ARRAY_FIELD = TEXT("Cities");

    /// <summary>
	/// Holds the name of our message log page.
	/// </summary>
    const FName MSG_LOG_NAME("Weast");
}


UENUM()
namespace EWeast
{
    enum TimeOfDay
    {
        EWT_Day,
        EWT_Night
    };
}


struct FWeatherDescriptor;

typedef TSharedPtr<FWeatherDescriptor> FWeatherDescriptorPtr;
typedef TSharedRef<FWeatherDescriptor> FWeatherDescriptorRef;

/**
 * A simple struct describes the available weather conditions.
 */
USTRUCT()
struct WEAST_API FWeatherDescriptor
{
    GENERATED_BODY()

    FWeatherDescriptor()
        : CodeName(NAME_None)
        , DisplayName(NAME_None)
        , Identifier(NAME_None)
        , IconName(NAME_None)
        , IconId(INDEX_NONE)
		, TimeOfDay(EWeast::EWT_Day)
    {
    }
    
    FWeatherDescriptor(int32 InIdentifier, const FName& InIconId, const FName& InCodeName, const FName& InDisplayName, const FName& InIconName, EWeast::TimeOfDay InTimeOfDay)
        : CodeName(InCodeName)
        , DisplayName(InDisplayName)
        , Identifier(InIconId)
        , IconName(InIconName)
        , IconId(InIdentifier)
        , TimeOfDay(InTimeOfDay)
    {
    }

    /**
     * Implementation(s)
     */
    
    /** Returns true if this weather condition is valid, false otherwise. */
    bool IsValid() const
    {
        return IconId != INDEX_NONE && !Identifier.IsNone() && !CodeName.IsNone() && !DisplayName.IsNone() && !IconName.IsNone();
    }

	FString GetTimeOfDay() const
    {
        FString TimeOfDayAsString = TEXT("Day");
	    switch (TimeOfDay)
	    {
	    case EWeast::EWT_Night:
            TimeOfDayAsString= TEXT("Night");
            break;

        case EWeast::EWT_Day:
	    default:
            break;
	    }
        return TimeOfDayAsString;
    }

    /**
     * Attribute(s)
     */

    /** Holds the code name. */
    UPROPERTY()
        FName CodeName;
    
    /** Holds the display name. */
    UPROPERTY()
        FName DisplayName;
    
    /** Holds the unique identifier of the icon. */
    UPROPERTY()
        FName Identifier;
    
    /** Holds the icon name. */
    UPROPERTY()
        FName IconName;

    /** Holds the weather condition identifier. */
    UPROPERTY()
        int32 IconId;

    UPROPERTY()
        TEnumAsByte<EWeast::TimeOfDay> TimeOfDay;
};

namespace UE::Weast
{
    /**
     * A simple class to hold all common items.
     */
    class WEAST_API FWeastCommon
    {
    private:

        /**
         * Default Constructor.
         */
        FWeastCommon() = default;

        /**
         * Attribute(s)
         */

    public:

        /**
         * Retrives the matching weather descriptor (if exists).
         */
        static void GetWeatherDescriptor(int32 InIconId, const FName& InIdentifier, FWeatherDescriptorRef& OutWeatherDescriptor);

        static FName GetWeatherDescriptorStyleName(int32 InIconId, const FName& InIdentifier, FString InStyle, FString InSize);

        static void GetWeatherDescriptors(TArray<FWeatherDescriptorPtr>& OutWeatherDescriptors);
        /**
         * Attribute(s)
         */

    private:

        /** Holds all available weather condition descriptors. */
        static TArray<FWeatherDescriptorPtr> WeatherDescriptors;
    };
}