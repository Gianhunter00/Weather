// Copyright (c) 2022 Maurious Paul Vincent. All rights reserved.

#include "Common/WeastCommon.h"

#define LOCTEXT_NAMESPACE "WeastCommon"

TArray<FWeatherDescriptorPtr> UE::Weast::FWeastCommon::WeatherDescriptors = {
	  MakeShared<FWeatherDescriptor>(200, TEXT("11d"), TEXT("ChanceTStorms.Day"), TEXT("Thunderstorms with light rain"), TEXT("chancetstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(201, TEXT("11d"), TEXT("ChanceTStorms.Day"), TEXT("Thunderstorms with rain"), TEXT("chancetstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(202, TEXT("11d"), TEXT("ChanceTStorms.Day"), TEXT("Thunderstorms with  heavy rain"), TEXT("chancetstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(210, TEXT("11d"), TEXT("TStorms.Day"), TEXT("Light Thunderstorms"), TEXT("tstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(211, TEXT("11d"), TEXT("TStorms.Day"), TEXT("Thunderstorms"), TEXT("tstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(212, TEXT("11d"), TEXT("TStorms.Day"), TEXT("Heavy thunderstorms"), TEXT("tstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(221, TEXT("11d"), TEXT("TStorms.Day"), TEXT("Ragged thunderstorms"), TEXT("tstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(230, TEXT("11d"), TEXT("TStorms.Day"), TEXT("Thunderstorms with light drizzle"), TEXT("tstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(231, TEXT("11d"), TEXT("TStorms.Day"), TEXT("Thunderstorms with drizzle"), TEXT("tstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(232, TEXT("11d"), TEXT("TStorms.Day"), TEXT("Thunderstorms with heavy drizzle"), TEXT("tstorms"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(300, TEXT("09d"), TEXT("ChanceFlurries.Day"), TEXT("Chance of Flurries"), TEXT("chanceflurries"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(301, TEXT("09d"), TEXT("Flurries.Day"), TEXT("Flurries"), TEXT("flurries"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(302, TEXT("09d"), TEXT("Flurries.Day"), TEXT("Heavy flurries"), TEXT("flurries"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(310, TEXT("09d"), TEXT("Flurries.Day"), TEXT("Light intensity Freezing Rain"), TEXT("flurries"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(311, TEXT("09d"), TEXT("ChanceSleet.Day"), TEXT("Chance of Freezing Rain"), TEXT("chancesleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(312, TEXT("09d"), TEXT("ChanceSleet.Day"), TEXT("Heavy intensity Freezing Rain"), TEXT("chancesleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(313, TEXT("09d"), TEXT("ChanceSleet.Day"), TEXT("Shower rain and drizzle"), TEXT("chancesleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(314, TEXT("09d"), TEXT("ChanceSleet.Day"), TEXT("Heavy shower rain and drizzle"), TEXT("chancesleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(321, TEXT("09d"), TEXT("ChanceSleet.Day"), TEXT("Shower of Freezing Rain"), TEXT("chancesleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(500, TEXT("10d"), TEXT("ChanceRain.Day"), TEXT("Light Rain"), TEXT("chancerain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(501, TEXT("10d"), TEXT("ChanceRain.Day"), TEXT("Chance of Rain"), TEXT("chancerain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(502, TEXT("10d"), TEXT("Rain.Day"), TEXT("Heavy Rain"), TEXT("rain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(503, TEXT("10d"), TEXT("Rain.Day"), TEXT("Very heavy Rain"), TEXT("rain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(504, TEXT("10d"), TEXT("Rain.Day"), TEXT("Extreme Rain"), TEXT("rain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(511, TEXT("13d"), TEXT("Sleet.Day"), TEXT("Freezing Rain"), TEXT("sleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(520, TEXT("09d"), TEXT("Rain.Day"), TEXT("Light intensity shower Rain"), TEXT("rain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(521, TEXT("09d"), TEXT("Rain.Day"), TEXT("Shower Rain"), TEXT("rain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(522, TEXT("09d"), TEXT("Rain.Day"), TEXT("Heavy intensity shower Rain"), TEXT("rain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(531, TEXT("09d"), TEXT("Rain.Day"), TEXT("Ragged shower Rain"), TEXT("rain"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(600, TEXT("13d"), TEXT("ChanceSnow.Day"), TEXT("Chance of Snow"), TEXT("chancesnow"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(601, TEXT("13d"), TEXT("Snow.Day"), TEXT("Snow"), TEXT("snow"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(602, TEXT("13d"), TEXT("Snow.Day"), TEXT("Heavy Snow"), TEXT("snow"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(611, TEXT("13d"), TEXT("Sleet.Day"), TEXT("Sleet"), TEXT("sleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(612, TEXT("13d"), TEXT("Sleet.Day"), TEXT("Light shower sleet"), TEXT("sleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(613, TEXT("13d"), TEXT("Sleet.Day"), TEXT("Shower sleet"), TEXT("sleet"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(615, TEXT("13d"), TEXT("Snow.Day"), TEXT("Light rain and snow"), TEXT("snow"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(616, TEXT("13d"), TEXT("Snow.Day"), TEXT("Rain and snow"), TEXT("snow"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(620, TEXT("13d"), TEXT("Snow.Day"), TEXT("Light shower snow"), TEXT("snow"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(621, TEXT("13d"), TEXT("Snow.Day"), TEXT("Shower snow"), TEXT("snow"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(622, TEXT("13d"), TEXT("Snow.Day"), TEXT("Heavy shower snow"), TEXT("snow"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(701, TEXT("50d"), TEXT("Haze.Day"), TEXT("Mist"), TEXT("hazy"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(711, TEXT("50d"), TEXT("Haze.Day"), TEXT("Smoke"), TEXT("hazy"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(721, TEXT("50d"), TEXT("Haze.Day"), TEXT("Haze"), TEXT("hazy"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(731, TEXT("50d"), TEXT("Fog.Day"), TEXT("Dust Sand"), TEXT("fog"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(741, TEXT("50d"), TEXT("Fog.Day"), TEXT("Fog"), TEXT("fog"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(751, TEXT("50d"), TEXT("Fog.Day"), TEXT("Sand"), TEXT("fog"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(761, TEXT("50d"), TEXT("Fog.Day"), TEXT("Dust"), TEXT("fog"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(762, TEXT("50d"), TEXT("Fog.Day"), TEXT("Ash"), TEXT("fog"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(771, TEXT("50d"), TEXT("Fog.Day"), TEXT("Squall"), TEXT("fog"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(781, TEXT("50d"), TEXT("Fog.Day"), TEXT("Tornado"), TEXT("fog"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(800, TEXT("01d"), TEXT("Clear.Day"), TEXT("Clear"), TEXT("clear"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(801, TEXT("02d"), TEXT("MostlySunny.Day"), TEXT("Mostly Sunny"), TEXT("mostlysunny"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(802, TEXT("03d"), TEXT("cloudy.Day"), TEXT("Cloudy"), TEXT("cloudy"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(803, TEXT("04d"), TEXT("PartlyCloudy.Day"), TEXT("Partly Cloudy"), TEXT("partlycloudy"), EWeast::EWT_Day)
	, MakeShared<FWeatherDescriptor>(804, TEXT("04d"), TEXT("MostlyCloudy.Day"), TEXT("Mostly Cloudy"), TEXT("mostlycloudy"), EWeast::EWT_Day)

	, MakeShared<FWeatherDescriptor>(200, TEXT("11n"), TEXT("ChanceTStorms.Night"), TEXT("Thunderstorms with light rain"), TEXT("nt_chancetstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(201, TEXT("11n"), TEXT("ChanceTStorms.Night"), TEXT("Thunderstorms with rain"), TEXT("nt_chancetstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(202, TEXT("11n"), TEXT("ChanceTStorms.Night"), TEXT("Thunderstorms with  heavy rain"), TEXT("nt_chancetstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(210, TEXT("11n"), TEXT("TStorms.Night"), TEXT("Light Thunderstorms"),TEXT("nt_tstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(211, TEXT("11n"), TEXT("TStorms.Night"), TEXT("Thunderstorms"),TEXT("nt_tstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(212, TEXT("11n"), TEXT("TStorms.Night"),TEXT("Heavy thunderstorms"), TEXT("nt_tstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(221, TEXT("11n"), TEXT("TStorms.Night"), TEXT("Ragged thunderstorms"), TEXT("nt_tstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(230, TEXT("11n"), TEXT("TStorms.Night"), TEXT("Thunderstorms with light drizzle"), TEXT("nt_tstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(231, TEXT("11n"), TEXT("TStorms.Night"), TEXT("Thunderstorms with drizzle"), TEXT("nt_tstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(232, TEXT("11n"), TEXT("TStorms.Night"), TEXT("Thunderstorms with heavy drizzle"), TEXT("nt_tstorms"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(300, TEXT("09n"), TEXT("ChanceFlurries.Night"), TEXT("Chance of Flurries"), TEXT("nt_chanceflurries"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(301, TEXT("09n"), TEXT("Flurries.Night"), TEXT("Flurries"), TEXT("nt_flurries"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(302, TEXT("09n"), TEXT("Flurries.Night"), TEXT("Heavy flurries"), TEXT("nt_flurries"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(310, TEXT("09n"), TEXT("Flurries.Night"), TEXT("Light intensity Freezing Rain"), TEXT("nt_flurries"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(311, TEXT("09n"), TEXT("ChanceSleet.Night"), TEXT("Chance of Freezing Rain"), TEXT("nt_chancesleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(312, TEXT("09n"), TEXT("ChanceSleet.Night"), TEXT("Heavy intensity Freezing Rain"), TEXT("nt_chancesleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(313, TEXT("09n"), TEXT("ChanceSleet.Night"), TEXT("Shower rain and drizzle"), TEXT("nt_chancesleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(314, TEXT("09n"), TEXT("ChanceSleet.Night"), TEXT("Heavy shower rain and drizzle"), TEXT("nt_chancesleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(321, TEXT("09n"), TEXT("ChanceSleet.Night"), TEXT("Shower of Freezing Rain"), TEXT("nt_chancesleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(500, TEXT("10n"), TEXT("ChanceRain.Night"), TEXT("Light Rain"), TEXT("nt_chancerain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(501, TEXT("10n"), TEXT("ChanceRain.Night"), TEXT("Chance of Rain"), TEXT("nt_chancerain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(502, TEXT("10n"), TEXT("Rain.Night"), TEXT("Heavy Rain"), TEXT("nt_rain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(503, TEXT("10n"), TEXT("Rain.Night"), TEXT("Very heavy Rain"), TEXT("nt_rain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(504, TEXT("10n"), TEXT("Rain.Night"), TEXT("Extreme Rain"), TEXT("nt_rain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(511, TEXT("13n"), TEXT("Sleet.Night"), TEXT("Freezing Rain"), TEXT("nt_sleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(520, TEXT("09n"), TEXT("Rain.Night"), TEXT("Light intensity shower Rain"), TEXT("nt_rain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(521, TEXT("09n"), TEXT("Rain.Night"), TEXT("Shower Rain"),  TEXT("nt_rain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(522, TEXT("09n"), TEXT("Rain.Night"), TEXT("Heavy intensity shower Rain"), TEXT("nt_rain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(531, TEXT("09n"), TEXT("Rain.Night"), TEXT("Ragged shower Rain"), TEXT("nt_rain"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(600, TEXT("13n"), TEXT("ChanceSnow.Night"), TEXT("Chance of Snow"), TEXT("nt_chancesnow"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(601, TEXT("13n"), TEXT("Snow.Night"), TEXT("Snow"), TEXT("nt_snow"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(602, TEXT("13n"), TEXT("Snow.Night"), TEXT("Heavy Snow"), TEXT("nt_snow"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(611, TEXT("13n"), TEXT("Sleet.Night"), TEXT("Sleet"), TEXT("nt_sleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(612, TEXT("13n"), TEXT("Sleet.Night"), TEXT("Light shower sleet"), TEXT("nt_sleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(613, TEXT("13n"), TEXT("Sleet.Night"), TEXT("Shower sleet"), TEXT("nt_sleet"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(615, TEXT("13n"), TEXT("Snow.Night"), TEXT("Light rain and snow"), TEXT("nt_snow"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(616, TEXT("13n"), TEXT("Snow.Night"), TEXT("Rain and snow"), TEXT("nt_snow"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(620, TEXT("13n"), TEXT("Snow.Night"), TEXT("Light shower snow"), TEXT("nt_snow"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(621, TEXT("13n"), TEXT("Snow.Night"), TEXT("Shower snow"), TEXT("nt_snow"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(622, TEXT("13n"), TEXT("Snow.Night"), TEXT("Heavy shower snow"), TEXT("nt_snow"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(701, TEXT("50n"), TEXT("Haze.Night"), TEXT("Mist"), TEXT("nt_hazy"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(711, TEXT("50n"), TEXT("Haze.Night"), TEXT("Smoke"), TEXT("nt_hazy"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(721, TEXT("50n"), TEXT("Haze.Night"), TEXT("Haze"), TEXT("nt_hazy"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(731, TEXT("50n"), TEXT("Fog.Night"), TEXT("Dust Sand"), TEXT("nt_fog"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(741, TEXT("50n"), TEXT("Fog.Night"), TEXT("Fog"), TEXT("nt_fog"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(751, TEXT("50n"), TEXT("Fog.Night"), TEXT("Sand"), TEXT("nt_fog"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(761, TEXT("50n"), TEXT("Fog.Night"), TEXT("Dust"), TEXT("nt_fog"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(762, TEXT("50n"), TEXT("Fog.Night"), TEXT("Ash"), TEXT("nt_fog"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(771, TEXT("50n"), TEXT("Fog.Night"), TEXT("Squall"), TEXT("nt_fog"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(781, TEXT("50n"), TEXT("Fog.Night"), TEXT("Tornado"), TEXT("nt_fog"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(800, TEXT("01n"), TEXT("Clear.Night"), TEXT("Clear"), TEXT("nt_clear"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(801, TEXT("02n"), TEXT("MostlySunny.Night"), TEXT("Mostly Sunny"), TEXT("nt_mostlysunny"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(802, TEXT("03n"), TEXT("cloudy.Night"), TEXT("Cloudy"), TEXT("nt_cloudy"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(803, TEXT("04n"), TEXT("PartlyCloudy.Night"), TEXT("Partly Cloudy"), TEXT("nt_partlycloudy"), EWeast::EWT_Night)
	, MakeShared<FWeatherDescriptor>(804, TEXT("04n"), TEXT("MostlyCloudy.Night"), TEXT("Mostly Cloudy"), TEXT("nt_mostlycloudy"), EWeast::EWT_Night)
};

void UE::Weast::FWeastCommon::GetWeatherDescriptor(int32 InIconId, const FName& InIdentifier, FWeatherDescriptorRef& OutWeatherDescriptor)
{
	OutWeatherDescriptor = WeatherDescriptors.Last().ToSharedRef();

	for (const FWeatherDescriptorPtr& WeatherDescriptor : WeatherDescriptors)
	{
		if (WeatherDescriptor->IconId == InIconId && WeatherDescriptor->Identifier == InIdentifier)
		{
			OutWeatherDescriptor = WeatherDescriptor.ToSharedRef();
		}
	}
}

FName UE::Weast::FWeastCommon::GetWeatherDescriptorStyleName(int32 InIconId, const FName& InIdentifier, FString InStyle, FString InSize)
{
	for (const FWeatherDescriptorPtr& WeatherDescriptor : WeatherDescriptors)
	{
		if (WeatherDescriptor->IconId == InIconId && WeatherDescriptor->Identifier == InIdentifier)
		{
			FStringFormatOrderedArguments FormatArgs;
			FormatArgs.Add(FStringFormatArg(WeatherDescriptor->CodeName.ToString()));
			FormatArgs.Add(FStringFormatArg(InStyle));
			FormatArgs.Add(FStringFormatArg(InSize));
			return FName(FString::Format(TEXT("Weast.Weather.{0}.{1}.{2}"), FormatArgs));
		}
	}
	return FName(TEXT(""));
}

void UE::Weast::FWeastCommon::GetWeatherDescriptors(TArray<FWeatherDescriptorPtr>& OutWeatherDescriptors)
{
	OutWeatherDescriptors = WeatherDescriptors;

}

#undef LOCTEXT_NAMESPACE