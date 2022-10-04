#pragma once

#include "CoreMinimal.h"
#include "Models/IWeastModel.h"
#include "Styling/WeastWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

class SWeastHour : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SWeastHour)
		: _CityGuid(FGuid())
		, _Hour(0)
		, _ImageSize(TEXT("ExtraLarge"))
	{}

	SLATE_ATTRIBUTE(FGuid, CityGuid)

	SLATE_ATTRIBUTE(int32, Hour)

	SLATE_ATTRIBUTE(FString, ImageSize)

	SLATE_END_ARGS()

public:
	WEASTEDITOR_API void Construct(const FArguments& InArgs, const IWeastModelRef& InModel);
	FName GetWeatherDescriptorStyleName(FString InStyleName, FString InSize) const;
	FText GetTemperatureUnit() const;

private:
	IWeastModelPtr Model;
	FGuid CityGuid;
	const FWeastWidgetStyle* WeastStyle;
	int32 Hour;
	FString ImageSize;
};