#include "Slate/Input/SWeastPinnedButton.h"

#include "Components/VerticalBox.h"
#include "Slate/Public/SlateOptMacros.h"

#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSeparator.h"

#define LOCTEXT_NAMESPACE "SWeastPinnedButton"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastPinnedButton::Construct(const FArguments& InArgs)
{
	CityGuid = InArgs._CityGuid;
	OnPinnedButtonClicked = InArgs._OnPinnedButtonClicked;
	ChildSlot
	[
		SNew(SButton)
		.ButtonStyle(InArgs._ButtonStyle)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.OnClicked_Lambda([this]()
		{
			if(OnPinnedButtonClicked.IsBound())
			{
				OnPinnedButtonClicked.Execute(CityGuid);
			}
			return FReply::Handled();
		})
		[
			SNew(SImage)
			.Visibility_Lambda([this]()
			{
				if(IsHovered())
				{
					return EVisibility::Visible;
				}
				return EVisibility::Collapsed;
			})
			.ColorAndOpacity(FSlateColor::UseForeground())
			.Image(InArgs._ButtonImage)
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE