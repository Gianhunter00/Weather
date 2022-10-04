#pragma once

#include "CoreMinimal.h"
#include "Models/IWeastModel.h"
#include "Styling/WeastWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

class SWeastMultiViewPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeastMultiViewPanel)
		: _CityGuid(FGuid())
		, _WidgetIndex(EWeastView::EWVL_Home)
		, _bUseActiveCity(false)
		, _ImageSize(TEXT("ExtraLarge"))
	{}


	SLATE_ATTRIBUTE(FGuid, CityGuid)

	SLATE_ATTRIBUTE(EWeastView::Layout, WidgetIndex)

	SLATE_ATTRIBUTE(bool, bUseActiveCity)

	SLATE_ATTRIBUTE(FString, ImageSize)

	SLATE_END_ARGS()

public:
	WEASTEDITOR_API void Construct(const FArguments& InArgs, const FWeastViewArgsRef InViewType, const IWeastModelRef& InModel);

private:
	IWeastModelPtr Model;
	FWeastViewArgsPtr WeastView;
	TAttribute<bool> UseActiveCity;
	FGuid CityGuid;

};
