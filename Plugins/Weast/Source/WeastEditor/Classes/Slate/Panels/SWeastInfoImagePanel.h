#pragma once

#include "CoreMinimal.h"
#include "Models/IWeastModel.h"

#include "Widgets/SCompoundWidget.h"

#include "Styling/WeastWidgetStyle.h"

class SWeastInfoImagePanel : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SWeastInfoImagePanel)
		: _CityGuid(FGuid())
		, _bUseActiveCity(false)
	{}

	SLATE_ATTRIBUTE(FGuid, CityGuid)

	SLATE_ATTRIBUTE(bool, bUseActiveCity)

	SLATE_END_ARGS()

public:

	WEASTEDITOR_API void Construct(const FArguments& InArgs, const FWeastViewArgsImages& InViewType, const IWeastModelRef& InModel);

	FText BuildValueText(FString InText, FString InUnit = TEXT("")) const;

	FText BuildValueText(FText InText, FString InUnit = TEXT("")) const;

	FText GetRainTextData() const;

	FText GetPressureTextData() const;

	FText GetWindSpeedTextData() const;

	FText GetSunriseTextData() const;

	FText GetSunsetTextData() const;

	//TODO: Add Function to get automatically the Unit

private:
	IWeastModelPtr Model;
	FGuid CityGuid;
	const FWeastWidgetStyle* WeastStyle;
	FWeastViewArgsImages WeastView;
	TAttribute<bool> UseActiveCity;
};
