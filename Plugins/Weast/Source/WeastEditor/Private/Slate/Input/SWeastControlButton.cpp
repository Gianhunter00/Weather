#include "Slate/Input/SWeastControlButton.h"

#include "Components/VerticalBox.h"
#include "Slate/Public/SlateOptMacros.h"

#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSeparator.h"

#define LOCTEXT_NAMESPACE "SWeastControlButton"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastControlButton::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SButton)
			.ButtonStyle(InArgs._ButtonStyle)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked(InArgs._OnWeastButtonClicked)
			[
				SNew(SImage)
				.Image(InArgs._ButtonImage)
			]
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE