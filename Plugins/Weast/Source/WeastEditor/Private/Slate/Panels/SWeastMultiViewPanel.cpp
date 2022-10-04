#include "Slate/Panels/SWeastMultiViewPanel.h"

#include "Components/HorizontalBox.h"
#include "Slate/Panels/SWeastTitlePanel.h"
#include "Slate/Panels/SWeastInfoImagePanel.h"

#include "SlateOptMacros.h"
#include "Styling/WeastWidgetStyle.h"

#define LOCTEXT_NAMESPACE "SMultiViewPanel"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastMultiViewPanel::Construct(const FArguments& InArgs, const FWeastViewArgsRef InViewType, const IWeastModelRef& InModel)
{
	CityGuid = InArgs._CityGuid.Get();
	WeastView = InViewType;
	UseActiveCity = InArgs._bUseActiveCity;
	Model = InModel;

	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.Padding(0.f, 0.f, 0.f, 10.f)
			.AutoHeight()
			[
				SNew(SWeastTitlePanel, Model.ToSharedRef())
				.ImageSize(InArgs._ImageSize)
				.CityGuid(CityGuid)
				.WidgetIndex(InArgs._WidgetIndex.Get())
			]
			+SVerticalBox::Slot()
			.Padding(0.f, 10.f)
			.AutoHeight()
			[
				SNew(SWeastInfoImagePanel, InViewType->ImagesInfo, Model.ToSharedRef())
				.bUseActiveCity(UseActiveCity)
				.CityGuid(CityGuid)
			]
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE