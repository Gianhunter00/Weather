// Copyright (c) 2022 Maurious Paul Vincent. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WeastSettings.generated.h"

UENUM()
namespace EWeastApp
{
	enum Theme
	{
		/** Dark theme. */
		EWT_Dark UMETA(DisplayName = "Dark"),

		/** Light theme. */
		EWT_Light UMETA(DisplayName = "Light"),
	};
}



UENUM()
namespace ETemperature
{
	enum Unit
	{
		/** Units in celsius. */
		ETU_Celsius UMETA(DisplayName = "Celsius"),

		/** Units in fahrenheit. */
		ETU_Fahrenheit UMETA(DisplayName = "Fahrenheit"),

		/** Units in Kelvin. */
		ETU_Kelvin UMETA(DisplayName = "Kelvin"),
	};
}

namespace ETemperature::Helper
{
	inline FString FieldValueBasedOnTemperature(ETemperature::Unit InTemperature)
	{
		FString Result = TEXT("");

		switch (InTemperature)
		{
		case ETemperature::Unit::ETU_Celsius:
			Result = TEXT("metric");
			break;

		case ETemperature::Unit::ETU_Fahrenheit:
			Result = TEXT("imperial");
			break;

		case ETemperature::Unit::ETU_Kelvin:
		default:
			Result = TEXT("standard");
			break;
		}
		return Result;
	}
}

/**
 * Global weast settings
 */
UCLASS(Config = Weast)
class WEAST_API UWeastSettings : public UDeveloperSettings
{
	GENERATED_BODY()

		//~ BEGIN : UDeveloperSettings Interface

public:

	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override;

	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override;

	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override;

#if WITH_EDITOR

	virtual FText GetSectionText() const override;

#endif // WITH_EDITOR

	//~ END : UDeveloperSettings Interface

	/**
	 * Implementation(s)
	 */

public:

	/**
	 * Retrieves the active theme.
	 */
	EWeastApp::Theme GetActiveTheme() const;

	/**
	 * Retrieves the unit of temperature.
	 */
	ETemperature::Unit GetTemperatureUnit() const;

	/**
	 * Retrieves bAutoRefresh.
	 */
	bool GetAutoRefresh() const;


	/**
	 * Retrieves RefreshFrequency.
	 */
	float GetRefreshFrequency() const;

	/**
	 * Attribute(s)
	 */

private:

	/**
	 * Holds the active theme applied.
	 *
	 * Upon changing this you should close and reopen the Weast Panel to take effect.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "General", Meta = (AllowPrivateAccess = "true", DisplayName = "Theme"))
		TEnumAsByte<EWeastApp::Theme> ActiveTheme = EWeastApp::EWT_Dark;

	/**
	 * Holds the temperature unit.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "General", Meta = (AllowPrivateAccess = "true", DisplayName = "Temp. Unit"))
		TEnumAsByte<ETemperature::Unit> TemperatureUnit = ETemperature::ETU_Celsius;

	UPROPERTY(Config, EditAnywhere, Category = "General", Meta = (AllowPrivateAccess = "true"))
		bool bAutoRefresh;

	UPROPERTY(DisplayName = "Refresh Frequency Minutes", Config, EditAnywhere, Category = "General", Meta = (AllowPrivateAccess = "true", EditCondition = "bAutoRefresh", EditConditionHides, UIMin = 6, ClampMin = 6))
		float RefreshFrequency;
};
