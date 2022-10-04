
#include "Slate/Output/SWeastImageWithText.h"

#include "Components/VerticalBox.h"
#include "Slate/Public/SlateOptMacros.h"

#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSeparator.h"

#define LOCTEXT_NAMESPACE "SWeastImageWithText"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastImageWithText::Construct(const FArguments& InArgs)
{
	const TSharedPtr<SHorizontalBox> HorizontalBoxWidget = SNew(SHorizontalBox);

	if (InArgs._ImageOrientation == EWeastView::EWVO_Left)
	{
		HorizontalBoxWidget->AddSlot()
			.VAlign(VAlign_Center)
			.AutoWidth()
			[
				BuildImage(InArgs._Image.Get())
			];
	}

	HorizontalBoxWidget->AddSlot()
		.Padding(4.f, 0.f)
		.VAlign(VAlign_Center)
		.AutoWidth()
		[
			SNew(SVerticalBox)
			
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.ColorAndOpacity(InArgs._TextColor)
				.Text(InArgs._Text)
				.Font(InArgs._Font)
			]
		];

	if (InArgs._ImageOrientation == EWeastView::EWVO_Right)
	{
		HorizontalBoxWidget->AddSlot()
			.VAlign(VAlign_Center)
			.AutoWidth()
			[
				BuildImage(InArgs._Image.Get())
			];
	}

	ChildSlot
		[
			HorizontalBoxWidget.ToSharedRef()
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<SWidget> SWeastImageWithText::BuildImage(const FSlateBrush* InImage)
{
	const TSharedPtr<SVerticalBox> ImageWidget = SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(2.f)
		[
			SNew(SImage)
			.Image(InImage)
		];

	return ImageWidget.ToSharedRef();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE