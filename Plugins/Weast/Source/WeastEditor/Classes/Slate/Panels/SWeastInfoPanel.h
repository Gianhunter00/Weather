#pragma once

#include "CoreMinimal.h"
#include "Models/IWeastModel.h"
#include "Styling/WeastWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

class SWeastInfoPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeastInfoPanel)
	{}


	SLATE_END_ARGS()

public:

	WEASTEDITOR_API void Construct(const FArguments& InArgs, const IWeastModelRef& InModel);
	TSharedRef<ITableRow> OnGenerateWidgetForDaily(TSharedPtr<FWeatherDailyInfo> InItem, const TSharedRef<STableViewBase>& OwnerTable);
	TSharedRef<ITableRow> OnGenerateWidgetForHourly(TSharedPtr<FWeatherHourlyInfo> InItem, const TSharedRef<STableViewBase>& OwnerTable);
	void OnActiveHourlyChanges(TArray<TSharedPtr<FWeatherHourlyInfo>>& InHourly);
	void OnActiveDailiesChanges(TArray<TSharedPtr<FWeatherDailyInfo>>& InDaily);
private:
	IWeastModelPtr Model;
	TSharedPtr<SListView<TSharedPtr<FWeatherDailyInfo>>> DaysListView;
	TSharedPtr<SListView<TSharedPtr<FWeatherHourlyInfo>>> HourlyListView;
	TArray<TSharedPtr<FWeatherDailyInfo>> Dailies;
	TArray<TSharedPtr<FWeatherHourlyInfo>> Hourly;
	const FWeastWidgetStyle* WeastStyle;
};
