
#include "Slate/Panels/SWeastControlButtonPanel.h"

#include "Slate/Input/SWeastControlButton.h"

#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "SWeastControlButtonPanel"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastControlButtonPanel::Construct(const FArguments& InArgs, const IWeastModelRef& InModel)
{
	Model = InModel;
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();
	WidgetSwitcherIndex = InArgs._WidgetSwitcherIndex;

	ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(0.25f)
			.Padding(4.f)
			[
				SNew(SBorder)
				.BorderImage_Lambda([this]()
					{
						if (WidgetSwitcherIndex)
						{
							if (*WidgetSwitcherIndex == 0)
							{
								return &WeastStyle->ControlButtonPressedIconBrush;
							}
						}
						return &WeastStyle->ButtonControlStyle.Normal;
					})
				[
					SNew(SWeastControlButton)
					.ButtonStyle(&WeastStyle->ButtonControlStyle)
					.ButtonImage(&WeastStyle->HomeIconBrush)
					.OnWeastButtonClicked_Lambda([this]()
					{
							if (WidgetSwitcherIndex)
							{
								*WidgetSwitcherIndex = 0;
							}
						return FReply::Handled();
					})
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(0.25f)
			.Padding(4.f)
			[
				SNew(SBorder)
				.BorderImage_Lambda([this]()
					{
						if (WidgetSwitcherIndex)
						{
							if (*WidgetSwitcherIndex == 1)
							{
								return &WeastStyle->ControlButtonPressedIconBrush;
							}
						}
						return &WeastStyle->ButtonControlStyle.Normal;
					})
				[
					SNew(SWeastControlButton)
					.ButtonStyle(&WeastStyle->ButtonControlStyle)
					.ButtonImage(&WeastStyle->AddIconBrush)
					.OnWeastButtonClicked_Lambda([this]()
					{
							if (WidgetSwitcherIndex)
							{
								*WidgetSwitcherIndex = 1;
							}
						return FReply::Handled();
					})
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(0.25f)
			.Padding(4.f)
			[
				SNew(SBorder)
				.BorderImage_Lambda([this]()
					{
						if (WidgetSwitcherIndex)
						{
							if (*WidgetSwitcherIndex == 2)
							{
								return &WeastStyle->ControlButtonPressedIconBrush;
							}
						}
						return &WeastStyle->ButtonControlStyle.Normal;
					})
				[
					SNew(SWeastControlButton)
					.ButtonStyle(&WeastStyle->ButtonControlStyle)
					.ButtonImage(&WeastStyle->InfoIconBrush)
					.OnWeastButtonClicked_Lambda([this]()
					{
							if (WidgetSwitcherIndex)
							{
								*WidgetSwitcherIndex = 2;
							}
						return FReply::Handled();
					})
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(0.25f)
			.Padding(4.f)
			[
				SNew(SWeastControlButton)
				.ButtonStyle(&WeastStyle->ButtonControlStyle)
				.ButtonImage(&WeastStyle->RefreshIconBrush)
				.OnWeastButtonClicked_Lambda([this]()
				{
					Model->RefreshData();
					return FReply::Handled();
				})
			]
		];

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE