#pragma once


#include "CoreMinimal.h"
#include "Models/IWeastModel.h"
#include "Styling/WeastWidgetStyle.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/SCompoundWidget.h"


template <typename ItemType>
class SWeastListView : public SListView<ItemType>
{
	DECLARE_DELEGATE_OneParam(FOnWeastListChange, TArray<ItemType>&)

public:
	SLATE_BEGIN_ARGS(SWeastListView<ItemType>)
		: _Orientation(EOrientation::Orient_Vertical)
		, _StartingList(TArray<ItemType>())
		, _OnWeastGenerateRow()
		, _OnWeastListChange()
	{}
	SLATE_ARGUMENT(EOrientation, Orientation)

	SLATE_ARGUMENT(TArray<ItemType>, StartingList)

	SLATE_EVENT(SListView<ItemType>::FOnGenerateRow, OnWeastGenerateRow)

	SLATE_EVENT(FOnWeastListChange, OnWeastListChange)

	SLATE_END_ARGS()
public:
	~SWeastListView();

	WEASTEDITOR_API void Construct(const typename SWeastListView<ItemType>::FArguments& InArgs, const IWeastModelRef& InModel);

	void OnWeastListChangeCallback();

private:
	IWeastModelPtr Model;
	const FWeastWidgetStyle* WeastStyle =nullptr;
	TArray<ItemType> WeastListArray;
	FOnWeastListChange OnWeastListChange;
};
