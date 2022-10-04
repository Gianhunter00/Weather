#pragma once

#include "CoreMinimal.h"
#include "Models/IWeastModel.h"

#include "Widgets/SCompoundWidget.h"

#include "Styling/WeastWidgetStyle.h"

class SWeastControlButtonPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeastControlButtonPanel)
		: _WidgetSwitcherIndex(nullptr)
	{ }

	SLATE_ARGUMENT(int32*, WidgetSwitcherIndex)

	SLATE_END_ARGS()
public:
	WEASTEDITOR_API void Construct(const FArguments& InArgs, const IWeastModelRef& InModel);

private:
	IWeastModelPtr Model;
	const FWeastWidgetStyle* WeastStyle;
	int32* WidgetSwitcherIndex;
};
