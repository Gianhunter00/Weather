#pragma once

#include "CoreMinimal.h"

#include "Styling/WeastWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

class SWeastImageWithText : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeastImageWithText)
	{}

	SLATE_ARGUMENT(TEnumAsByte<EWeastView::Orientation>, ImageOrientation)

	SLATE_ATTRIBUTE(FText, Text)

	SLATE_ARGUMENT(FSlateFontInfo, Font)

	SLATE_ARGUMENT(FLinearColor, TextColor)

	SLATE_ATTRIBUTE(const FSlateBrush*, Image)

	SLATE_END_ARGS()

public:

	WEASTEDITOR_API void Construct(const FArguments& InArgs);

	TSharedRef<SWidget> BuildImage(const FSlateBrush* InImage);
};