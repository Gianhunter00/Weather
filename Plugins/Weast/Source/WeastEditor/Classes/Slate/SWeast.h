#pragma once

#include "CoreMinimal.h"

#include "Models/IWeastModel.h"

#include "Styling/WeastWidgetStyle.h"

#include "Widgets/SCompoundWidget.h"

class SWeast : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeast)
	{}

	SLATE_END_ARGS()

public:

	SWeast();

	~SWeast();

public:

	WEASTEDITOR_API void Construct(	const FArguments& InArgs, 
									const TSharedRef<SDockTab>& ConstructUnderMajorTab,
									const TSharedPtr<SWindow>& ConstructUnderWindow, 
									const IWeastModelRef& InModel);

private:
	IWeastModelPtr Model;
	const FWeastWidgetStyle* WeastStyle;
	int32 WidgetSwitcherIndex;
};
