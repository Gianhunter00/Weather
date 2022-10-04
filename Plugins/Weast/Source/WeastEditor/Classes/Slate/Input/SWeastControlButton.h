#pragma once

#include "CoreMinimal.h"
#include "Widgets/Input/SButton.h"

class SWeastControlButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeastControlButton)
		: _ButtonImage(FStyleDefaults::GetNoBrush())
		, _ButtonStyle(NULL)
		, _OnWeastButtonClicked()
	{}

	SLATE_ARGUMENT(const FSlateBrush*, ButtonImage)

	SLATE_ARGUMENT(const FButtonStyle*, ButtonStyle)

	SLATE_EVENT(FOnClicked, OnWeastButtonClicked)

	SLATE_END_ARGS()
public:
	WEASTEDITOR_API void Construct(const FArguments& InArgs);
};
