
#include "Slate/Panels/SWeastHomePanel.h"

#include "Slate/Panels/SWeastMultiViewPanel.h"

#include "SlateOptMacros.h"
#include "Styling/WeastWidgetStyle.h"

#define LOCTEXT_NAMESPACE "SWeastInfoPanel"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastHomePanel::Construct(const FArguments& InArgs, const IWeastModelRef& InModel)
{
	Model = InModel;

	ChildSlot
		[
			SNew(SBox)
			.VAlign(VAlign_Center)
			[
				SNew(SWeastMultiViewPanel, FViewArgsFactory::CreateInfoCurrentViewArgs(), Model.ToSharedRef())
				.bUseActiveCity(true)
				.ImageSize("XXL")
				.WidgetIndex(EWeastView::EWVL_Home)
			]
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE