#pragma once

#include "CoreMinimal.h"
#include "Models/IWeastModel.h"
#include "Styling/SlateTypes.h"

#include "Styling/WeastWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

class SWeastTitlePanel : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SWeastTitlePanel)
		: _CityGuid(FGuid())
		, _WidgetIndex(EWeastView::EWVL_Home)
		, _ImageSize(TEXT("ExtraLarge"))
	{}

	SLATE_ATTRIBUTE(FGuid, CityGuid)

	SLATE_ATTRIBUTE(EWeastView::Layout, WidgetIndex)

	SLATE_ATTRIBUTE(FString, ImageSize)

	SLATE_END_ARGS()

public:

	WEASTEDITOR_API void Construct(const FArguments& InArgs, const IWeastModelRef& InModel);

private:

	TSharedRef<SWidget> BuildHomeLayout() const;

	TSharedRef<SWidget> BuildPinnedLayout() const;

	TSharedRef<SWidget> BuildInfoLayout() const;

	FText GetTemperatureUnit() const;

	FName GetWeatherDescriptorStyleName(FString InStyleName, FString InSize, bool bUseActive = false) const;

private:

	IWeastModelPtr Model;
	const FWeastWidgetStyle* WeastStyle;
	FString ImageSize;
	TMap<TEnumAsByte<EWeastView::Orientation>, TSharedPtr<SWidget>> OrientationWidgetMap;
	TAttribute<bool> UseActiveCity;
	FGuid CityGuid;
};
