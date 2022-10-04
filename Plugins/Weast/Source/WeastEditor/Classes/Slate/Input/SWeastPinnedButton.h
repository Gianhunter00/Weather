#pragma once

#include "CoreMinimal.h"

#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnPinnedButtonClicked, FGuid)

class SWeastPinnedButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeastPinnedButton)
		: _ButtonImage(FStyleDefaults::GetNoBrush())
		, _ButtonStyle(NULL)
		, _CityGuid(FGuid())
		, _OnPinnedButtonClicked()
	{}

	SLATE_ARGUMENT(const FSlateBrush*, ButtonImage)

	SLATE_ARGUMENT(const FButtonStyle*, ButtonStyle)

	SLATE_ARGUMENT(FGuid, CityGuid)

	SLATE_EVENT(FOnPinnedButtonClicked, OnPinnedButtonClicked)

	SLATE_END_ARGS()

public:
	WEASTEDITOR_API void Construct(const FArguments& InArgs);

private:
	FGuid CityGuid;
	FOnPinnedButtonClicked OnPinnedButtonClicked;
};
