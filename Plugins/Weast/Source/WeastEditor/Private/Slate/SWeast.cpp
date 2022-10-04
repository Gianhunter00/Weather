
#include "Slate/SWeast.h"

#include "Slate/Panels/SWeastControlButtonPanel.h"
#include "Slate/Panels/SWeastInfoPanel.h"
#include "Slate/Panels/SWeastHomePanel.h"
#include "Slate/Panels/SWeastPinnedPanel.h"
#include "Slate/Private/Framework/Docking/SDockingArea.h"
#include "Slate/Public/SlateOptMacros.h"

#include "Styling/WeastStyle.h"

#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Notifications/SProgressBar.h"

#define LOCTEXT_NAMESPACE "SWeast"

SWeast::SWeast()
{
	
}

SWeast::~SWeast()
{
	if (Model.IsValid())
	{
		Model.Reset();
	}
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeast::Construct(	const FArguments& InArgs, 
						const TSharedRef<SDockTab>& ConstructUnderMajorTab, 
						const TSharedPtr<SWindow>& ConstructUnderWindow, 
						const IWeastModelRef& InModel)
{
	Model = InModel;
	WidgetSwitcherIndex = 0;
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();

	ChildSlot
		[
			SNew(SBorder)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(new FSlateColorBrush(WeastStyle->BackgroundColor))
			[
				SNew(SVerticalBox)
				//SSwitcher based on input

				+ SVerticalBox::Slot()
				.FillHeight(0.8f)
				[
					SNew(SWidgetSwitcher)
					.WidgetIndex_Lambda([this]()
					{
						if(Model.IsValid())
						{
							return Model->HasFinishedLoading() ? 1 : 0;
						}
						return 0;
					})
					+ SWidgetSwitcher::Slot()
					[
						SNew(SBox)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.Padding(0.f, 5.f)
							.AutoHeight()
							[
								SNew(STextBlock)
								.TextStyle(&WeastStyle->TitleTextStyle)
								.ColorAndOpacity(WeastStyle->TextColor)
								.Text(LOCTEXT("ProgressBarLabel", "Loading Data From API..."))
							]
							+ SVerticalBox::Slot()
							.Padding(10.f, 0.f)
							[
								SNew(SProgressBar)
								.BarFillType(EProgressBarFillType::LeftToRight)
								.BarFillStyle(EProgressBarFillStyle::Scale)
								.Percent_Lambda([this]()
									{
										if (Model.IsValid())
										{
											return Model->LoadingPercentage();
										}
										return 0.f;
									})
							]
						]
					]
					+ SWidgetSwitcher::Slot()
					[
						SNew(SWidgetSwitcher)
						.WidgetIndex_Lambda([this]()
						{
							return WidgetSwitcherIndex;
						})

						//HomePanel
						+SWidgetSwitcher::Slot()
						[
							SNew(SWeastHomePanel, Model.ToSharedRef())
						]

						//PinnedPanel
						+ SWidgetSwitcher::Slot()
						[
							SNew(SWeastPinnedPanel, Model.ToSharedRef())
						]

						//InfoPanel
						+ SWidgetSwitcher::Slot()
						[
							SNew(SWeastInfoPanel, Model.ToSharedRef())
						]
					]
				]

				+ SVerticalBox::Slot()
				.FillHeight(0.1f)
				.Padding(5.f, 10.f)
				[
					SNew(SBorder)
					.BorderImage(&WeastStyle->ButtonsPanelIconBrush)
					[
						SNew(SWeastControlButtonPanel, Model.ToSharedRef())
						.WidgetSwitcherIndex(&WidgetSwitcherIndex)
					]
				]
			]
		];
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE