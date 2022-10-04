
#include "Slate/Panels/SWeastInfoPanel.h"

#include "Components/HorizontalBox.h"
#include "Slate/Output/SWeastDay.h"
#include "Slate/Output/SWeastHour.h"
#include "Slate/Output/SWeastListView.h"
#include "Slate/Panels/SWeastMultiViewPanel.h"
#include "SlateOptMacros.h"
#include "Styling/WeastStyle.h"
#include "Styling/WeastWidgetStyle.h"
#include "Widgets/Layout/SScrollBox.h"

#define LOCTEXT_NAMESPACE "SWeastHomePanel"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastInfoPanel::Construct(const FArguments& InArgs, const IWeastModelRef& InModel)
{
	Model = InModel;
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();
	TArray<TSharedPtr<FWeatherHourlyInfo>> StartingListHourly;
	TArray<TSharedPtr<FWeatherDailyInfo>> StartingListDaily;
	OnActiveDailiesChanges(StartingListDaily);
	OnActiveHourlyChanges(StartingListHourly);

	ChildSlot
		[
			SNew(SVerticalBox)

			//MultiView
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f,0.f,0.f,10.f)
			[
				SNew(SWeastMultiViewPanel, FViewArgsFactory::CreateHomeViewArgs(), Model.ToSharedRef())
				.bUseActiveCity(true)
				.WidgetIndex(EWeastView::EWVL_Info)
			]

			//TextBlock Today
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.Padding(6.f, 0.f)
			.AutoHeight()
			[
				SNew(STextBlock)
				.Font(WeastStyle->CaptionTextStyle.Font)
				.ColorAndOpacity(WeastStyle->TextColor)
				.Text(LOCTEXT("ListDaily", "Today"))
			]

			//Hourly list
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f)
			[
				SNew(SWeastListView<TSharedPtr<FWeatherHourlyInfo>>, Model.ToSharedRef())
				.StartingList(StartingListHourly)
				.Orientation(EOrientation::Orient_Horizontal)
				.OnWeastGenerateRow(this, &SWeastInfoPanel::OnGenerateWidgetForHourly)
				.OnWeastListChange(this, &SWeastInfoPanel::OnActiveHourlyChanges)
			]

			//Day List
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			.Padding(0.f, 8.f)
			[
				SNew(SWeastListView<TSharedPtr<FWeatherDailyInfo>>, Model.ToSharedRef())
				.StartingList(StartingListDaily)
				.Orientation(EOrientation::Orient_Vertical)
				.OnWeastGenerateRow(this, &SWeastInfoPanel::OnGenerateWidgetForDaily)
				.OnWeastListChange(this, &SWeastInfoPanel::OnActiveDailiesChanges)
				
			] 
		];
}

TSharedRef<ITableRow> SWeastInfoPanel::OnGenerateWidgetForDaily(TSharedPtr<FWeatherDailyInfo> InItem,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	if(!Model.IsValid() || !Model->HasFinishedLoading())
	{
		return SNew(STableRow<TSharedPtr<FWeatherDailyInfo>>, OwnerTable);
	}
	return SNew(STableRow<TSharedPtr<FWeatherDailyInfo>>, OwnerTable)
		.Style(&WeastStyle->TableRowViewStyle)
		.Padding(FMargin(0.f, 10.f))
		.Content()
		[
			SNew(SWeastDay, Model.ToSharedRef())
			.DayAfterThis(InItem->DayAfterToday)
			.CityGuid(Model->GetActiveCity()->Id)
			.ImageSize(TEXT("Medium"))
		];
}

TSharedRef<ITableRow> SWeastInfoPanel::OnGenerateWidgetForHourly(TSharedPtr<FWeatherHourlyInfo> InItem,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	if (!Model.IsValid() || !Model->HasFinishedLoading())
	{
		return SNew(STableRow<TSharedPtr<FWeatherHourlyInfo>>, OwnerTable);
	}
	return SNew(STableRow<TSharedPtr<FWeatherHourlyInfo>>, OwnerTable)
		.Style(&WeastStyle->TableRowViewStyle)
		.Padding(FMargin(10.f, 0.f))
		.Content()
		[
			SNew(SWeastHour, Model.ToSharedRef())
			.Hour(InItem->Hour)
			.CityGuid(Model->GetActiveCity()->Id)
			.ImageSize(TEXT("Medium"))
		];
}

void SWeastInfoPanel::OnActiveHourlyChanges(TArray<TSharedPtr<FWeatherHourlyInfo>>& InHourly)
{
	if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetActiveCity().IsValid())
	{
		Model->PopulateHourlyOnActiveCity(InHourly);
	}
}

void SWeastInfoPanel::OnActiveDailiesChanges(TArray<TSharedPtr<FWeatherDailyInfo>>& InDaily)
{
	if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetActiveCity().IsValid())
	{
		Model->PopulateDailiesOnActiveCity(InDaily);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE