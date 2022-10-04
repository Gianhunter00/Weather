#pragma once

#include "CoreMinimal.h"
#include "Models/IWeastModel.h"
#include "Styling/WeastWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SUniformGridPanel.h"

class SWeastPinnedPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeastPinnedPanel)
	{}


	SLATE_END_ARGS()

public:

	~SWeastPinnedPanel();

	WEASTEDITOR_API void Construct(const FArguments& InArgs, const IWeastModelRef& InModel);

	void OnSearchBoxTextChanged(const FText& InText);

	bool CityHasTextInAnyParameter(const FText& InSearchText, TSharedPtr<FWeatherCityRoute> InCity) const;

	void PopulateGrid();

	void PopulateGrid(const FText& InSearchText);

	void AddCitySlot(int32 InColumn, int32 InRow, FGuid InId);

	EVisibility PinnedVisibility(FGuid InId) const;

	EVisibility FavouriteVisibility(FGuid InId) const;

private:
	IWeastModelPtr Model;
	const FWeastWidgetStyle* WeastStyle;
	TSharedPtr<SUniformGridPanel> Grid;
	const int32 NumberOfColumns = 2;
};
