
#include "Slate/Output/SWeastListView.h"

#define LOCTEXT_NAMESPACE "SWeastListView"

template <typename ItemType>
SWeastListView<ItemType>::~SWeastListView()
{
	if(Model.IsValid())
	{
		Model->OnActiveCityChange().RemoveAll(this);
	}
}

template <typename ItemType>
void SWeastListView<ItemType>::Construct(const typename SWeastListView<ItemType>::FArguments& InArgs, const IWeastModelRef& InModel)
{
	Model = InModel;
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();
	OnWeastListChange = InArgs._OnWeastListChange;
	WeastListArray = InArgs._StartingList;

	if (Model.IsValid())
	{
		Model->OnActiveCityChange().AddSP(this, &SWeastListView::OnWeastListChangeCallback);
	}

	typename SListView<ItemType>::FArguments SuperArgs = SListView<ItemType>::FArguments();

	SuperArgs.ScrollbarVisibility(EVisibility::Collapsed);
	SuperArgs.ListItemsSource(&WeastListArray);
	SuperArgs.ListViewStyle(&WeastStyle->TableViewStyle);
	SuperArgs.Orientation(InArgs._Orientation);
	SuperArgs.OnGenerateRow(InArgs._OnWeastGenerateRow);

	SListView<ItemType>::Construct(SuperArgs);
}

template <typename ItemType>
void SWeastListView<ItemType>::OnWeastListChangeCallback()
{
	if(OnWeastListChange.IsBound())
	{
		OnWeastListChange.Execute(WeastListArray);
		SListView<ItemType>::RequestListRefresh();
	}
}

#undef LOCTEXT_NAMESPACE