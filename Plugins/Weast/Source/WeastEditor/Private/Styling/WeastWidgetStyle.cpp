// Copyright (c) 2022 Maurious Paul Vincent. All rights reserved.

#include "WeastWidgetStyle.h"

#include "Settings/WeastSettings.h"
#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"
#include "Styling/WeastStyle.h"

//Ask for Static TypeName

/**
 * FWeastWidgetStyle
 */

const FName FWeastWidgetStyle::TypeName(TEXT("FWeastWidgetStyle"));
const FString FWeastWidgetStyle::StyleName(TEXT(""));

FWeastWidgetStyle::FWeastWidgetStyle()
{
	//SetupBrushStyles();

	SetupTextStyles();

	SetupButtonStyles();

	SetupColorStyles();

	SetupTableRowStyles();

	SetupSearchBoxStyles();
}

FWeastWidgetStyle::~FWeastWidgetStyle()
{
}

void FWeastWidgetStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	ButtonControlStyle.GetResources(OutBrushes);
	ButtonLeftStyle.GetResources(OutBrushes);
	ButtonRightStyle.GetResources(OutBrushes);
	TableRowViewStyle.GetResources(OutBrushes);
	TableViewStyle.GetResources(OutBrushes);
	SearchBoxStyle.GetResources(OutBrushes);
	//TODO: Add All Brushes that i created

	//Images
	OutBrushes.Add(&AddIconBrush);
	OutBrushes.Add(&PressureIconBrush);
	OutBrushes.Add(&HomeIconBrush);
	OutBrushes.Add(&InfoIconBrush);
	OutBrushes.Add(&RainIconBrush);
	OutBrushes.Add(&WindIconBrush);
	OutBrushes.Add(&BehindTextIconBrush);
	OutBrushes.Add(&ButtonsPanelIconBrush);
	OutBrushes.Add(&FavouriteIconBrush);
	OutBrushes.Add(&PinIconBrush);
	OutBrushes.Add(&FavouriteIconBrush);
	OutBrushes.Add(&LocationIconBrush);
	OutBrushes.Add(&CurveIconBrush);

	//Button
	OutBrushes.Add(&ControlButtonHoveredIconBrush);
	OutBrushes.Add(&ControlButtonPressedIconBrush);
	OutBrushes.Add(&PinnedButtonHoveredLeftIconBrush);
	OutBrushes.Add(&PinnedButtonHoveredRightIconBrush);
	OutBrushes.Add(&PinnedButtonPressedLeftIconBrush);
	OutBrushes.Add(&PinnedButtonPressedRightIconBrush);
	//ListViewRow
	OutBrushes.Add(&TableRowHoveredBrush);
	OutBrushes.Add(&TableRowNormalBrush);
	OutBrushes.Add(&TableRowSelectedBrush);
	//Separator
	OutBrushes.Add(&SeparatorBrush);
	//Border
	OutBrushes.Add(&PinnedBorderBrush);
	//ContentArea
	OutBrushes.Add(&ContentAreaBrush);
}

const FName FWeastWidgetStyle::GetTypeName() const
{
	return TypeName;
}

const FString FWeastWidgetStyle::GetStyleName() const
{
	return StyleName;
}

const FWeastWidgetStyle& FWeastWidgetStyle::GetDefault()
{
	static FWeastWidgetStyle Default;
	return Default;
}

const FWeastWidgetStyle* FWeastWidgetStyle::GetCurrentStyle()
{
	const FWeastWidgetStyle* WeastStyle;
	if (const UWeastSettings* WeastSettings = GetMutableDefault<UWeastSettings>())
	{
		switch (WeastSettings->GetActiveTheme())
		{

		case EWeastApp::EWT_Light:
			WeastStyle = &FWeastStyle::Get().GetWidgetStyle<FWeastLightStyle>("Weast.Theme.Light");
			break;

		case EWeastApp::EWT_Dark:
		default:
			WeastStyle = &FWeastStyle::Get().GetWidgetStyle<FWeastDarkStyle>("Weast.Theme.Dark");
			break;
		}
	}
	else
	{
		WeastStyle = &GetDefault();
	}
	return WeastStyle;
}

void FWeastWidgetStyle::SetupTextStyles()
{
	BodyTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("Regular", 12.f))
		.SetColorAndOpacity(FSlateColor::UseForeground())
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::Black)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	CaptionTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("Medium", 15.f))
		.SetColorAndOpacity(FSlateColor::UseForeground())
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::Black)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	SubtitleTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("SemiBold", 18.f))
		.SetColorAndOpacity(FSlateColor::UseForeground())
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::Black)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	TitleTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("SemiBold", 21.f))
		.SetColorAndOpacity(FSlateColor::UseForeground())
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::Black)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));
}

void FWeastWidgetStyle::SetupButtonStyles()
{
	ButtonControlStyle = FButtonStyle();
	ButtonLeftStyle = FButtonStyle();
	ButtonRightStyle = FButtonStyle();
}

void FWeastWidgetStyle::SetupSearchBoxStyles()
{
	SearchBoxStyle = FSearchBoxStyle();
}

void FWeastWidgetStyle::SetupColorStyles()
{
	TextColor = FLinearColor::White;
	BackgroundColor = FLinearColor::Black;
}

void FWeastWidgetStyle::SetupTableRowStyles()
{
	TableRowViewStyle = FTableRowStyle();
}

/**
 * FWeastDarkStyle
 */

const FName FWeastDarkStyle::TypeName(TEXT("FWeastDarkStyle"));
const FString FWeastDarkStyle::StyleName(TEXT("Dark"));

FWeastDarkStyle::FWeastDarkStyle()
{
	SetupTextStyles();

	SetupButtonStyles();

	SetupColorStyles();

	SetupTableRowStyles();
}

FWeastDarkStyle::~FWeastDarkStyle()
{
}

void FWeastDarkStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	FWeastWidgetStyle::GetResources(OutBrushes);
}

const FName FWeastDarkStyle::GetTypeName() const
{
	return TypeName;
}

const FString FWeastDarkStyle::GetStyleName() const
{
	return StyleName;
}

void FWeastDarkStyle::SetupTextStyles()
{
	BodyTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("Regular", 12.f))
		.SetColorAndOpacity(FStyleColors::White)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::White)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	CaptionTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("Medium", 15.f))
		.SetColorAndOpacity(FStyleColors::White)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::White)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	SubtitleTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("SemiBold", 18.f))
		.SetColorAndOpacity(FStyleColors::White)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::White)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	TitleTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("SemiBold", 21.f))
		.SetColorAndOpacity(FStyleColors::White)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::White)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));
}

void FWeastDarkStyle::SetupColorStyles()
{
	TextColor = FLinearColor(FColor(241, 242, 246));
	BackgroundColor = FLinearColor(FColor(47, 53, 66));
}

void FWeastDarkStyle::SetupSearchBoxStyles()
{
	SearchBoxStyle = FCoreStyle::Get().GetWidgetStyle<FSearchBoxStyle>("SearchBox");
	FEditableTextBoxStyle EditableTextBoxStyle = FEditableTextBoxStyle();
	EditableTextBoxStyle.SetFont(FWeastStyle::GetDefaultFontStyle("Regular", 12.f));
	EditableTextBoxStyle.SetBackgroundImageFocused(BehindTextIconBrush);
	EditableTextBoxStyle.SetBackgroundImageHovered(BehindTextIconBrush);
	EditableTextBoxStyle.SetBackgroundImageNormal(BehindTextIconBrush);
	EditableTextBoxStyle.SetForegroundColor(TextColor);
	EditableTextBoxStyle.SetFocusedForegroundColor(TextColor);
	SearchBoxStyle.SetTextBoxStyle(EditableTextBoxStyle);
}

void FWeastDarkStyle::SetupButtonStyles()
{
	ButtonControlStyle = FAppStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton");
	ButtonControlStyle.SetPressedPadding(FMargin(0.f, 2.f, 2.f, 0.f))
		.SetHovered(ControlButtonHoveredIconBrush)
		.SetPressed(ControlButtonPressedIconBrush)
		.SetNormal(FSlateColorBrush(FLinearColor::Transparent));

	ButtonLeftStyle = FAppStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton");
	ButtonLeftStyle.SetPressedPadding(FMargin(0.f, 2.f, 2.f, 0.f))
		.SetHovered(PinnedButtonHoveredLeftIconBrush)
		.SetPressed(PinnedButtonPressedLeftIconBrush)
		.SetNormal(FSlateColorBrush(FLinearColor::Transparent));

	ButtonRightStyle = FAppStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton");
	ButtonRightStyle.SetPressedPadding(FMargin(0.f, 2.f, 2.f, 0.f))
		.SetHovered(PinnedButtonHoveredRightIconBrush)
		.SetPressed(PinnedButtonPressedRightIconBrush)
		.SetNormal(FSlateColorBrush(FLinearColor::Transparent));
}

void FWeastDarkStyle::SetupTableRowStyles()
{
	TableViewStyle = FTableViewStyle()
		.SetBackgroundBrush(FSlateColorBrush(FLinearColor(FColor(47, 53, 66))));

	TableRowViewStyle = FTableRowStyle()
		.SetEvenRowBackgroundBrush(TableRowNormalBrush)
		.SetEvenRowBackgroundHoveredBrush(TableRowHoveredBrush)

		.SetOddRowBackgroundBrush(TableRowNormalBrush)
		.SetOddRowBackgroundHoveredBrush(TableRowHoveredBrush)

		.SetSelectorFocusedBrush(TableRowSelectedBrush)

		.SetInactiveBrush(TableRowSelectedBrush)
		.SetInactiveHoveredBrush(TableRowSelectedBrush)

		.SetActiveBrush(TableRowSelectedBrush)
		.SetActiveHoveredBrush(TableRowSelectedBrush);
}

const FWeastDarkStyle& FWeastDarkStyle::GetDefault()
{
	static FWeastDarkStyle Default;
	return Default;
}

/**
 * FWeastLightStyle
 */

const FName FWeastLightStyle::TypeName(TEXT("FWeastLightStyle"));
const FString FWeastLightStyle::StyleName(TEXT("Light"));

FWeastLightStyle::FWeastLightStyle()
{
	SetupTextStyles();

	SetupButtonStyles();

	SetupColorStyles();

	SetupTableRowStyles();
}

FWeastLightStyle::~FWeastLightStyle()
{
}

void FWeastLightStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	FWeastWidgetStyle::GetResources(OutBrushes);
}

const FName FWeastLightStyle::GetTypeName() const
{
	return TypeName;
}

const FString FWeastLightStyle::GetStyleName() const
{
	return StyleName;
}

void FWeastLightStyle::SetupTextStyles()
{
	BodyTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("Regular", 12.f))
		.SetColorAndOpacity(FStyleColors::Black)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::Black)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	CaptionTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("Medium", 15.f))
		.SetColorAndOpacity(FStyleColors::Black)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::Black)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	SubtitleTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("SemiBold", 18.f))
		.SetColorAndOpacity(FStyleColors::Black)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::Black)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));

	TitleTextStyle = FTextBlockStyle()
		.SetFont(FWeastStyle::GetDefaultFontStyle("SemiBold", 21.f))
		.SetColorAndOpacity(FStyleColors::Black)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetSelectedBackgroundColor(FStyleColors::Highlight)
		.SetHighlightColor(FStyleColors::Black)
		.SetHighlightShape(FSlateColorBrush(FStyleColors::AccentGreen));
}

void FWeastLightStyle::SetupColorStyles()
{
	TextColor = FLinearColor(FColor(74, 80, 88));
	BackgroundColor = FLinearColor(FColor(206, 214, 224));
}

void FWeastLightStyle::SetupSearchBoxStyles()
{
	SearchBoxStyle = FCoreStyle::Get().GetWidgetStyle<FSearchBoxStyle>("SearchBox");
	FEditableTextBoxStyle EditableTextBoxStyle = FEditableTextBoxStyle();
	EditableTextBoxStyle.SetFont(FWeastStyle::GetDefaultFontStyle("Regular", 12.f));
	EditableTextBoxStyle.SetBackgroundImageFocused(BehindTextIconBrush);
	EditableTextBoxStyle.SetBackgroundImageHovered(BehindTextIconBrush);
	EditableTextBoxStyle.SetBackgroundImageNormal(BehindTextIconBrush);
	EditableTextBoxStyle.SetForegroundColor(TextColor);
	EditableTextBoxStyle.SetFocusedForegroundColor(TextColor);
	SearchBoxStyle.SetTextBoxStyle(EditableTextBoxStyle);
}

void FWeastLightStyle::SetupButtonStyles()
{
	ButtonControlStyle = FAppStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton");
	ButtonControlStyle.SetPressedPadding(FMargin(0.f, 2.f, 2.f, 0.f))
				.SetHovered(ControlButtonHoveredIconBrush)
				.SetPressed(ControlButtonPressedIconBrush)
				.SetNormal(FSlateColorBrush(FLinearColor::Transparent));

	ButtonLeftStyle = FAppStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton");
	ButtonLeftStyle.SetPressedPadding(FMargin(0.f, 2.f, 2.f, 0.f))
		.SetHovered(PinnedButtonHoveredLeftIconBrush)
		.SetPressed(PinnedButtonPressedLeftIconBrush)
		.SetNormal(FSlateColorBrush(FLinearColor::Transparent));

	ButtonRightStyle = FAppStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton");
	ButtonRightStyle.SetPressedPadding(FMargin(0.f, 2.f, 2.f, 0.f))
		.SetHovered(PinnedButtonHoveredRightIconBrush)
		.SetPressed(PinnedButtonPressedRightIconBrush)
		.SetNormal(FSlateColorBrush(FLinearColor::Transparent));
}

void FWeastLightStyle::SetupTableRowStyles()
{
	TableViewStyle = FTableViewStyle()
		.SetBackgroundBrush(FSlateColorBrush(FLinearColor(FColor(206, 214, 224))));

	TableRowViewStyle = FTableRowStyle()
		.SetEvenRowBackgroundBrush(TableRowNormalBrush)
		.SetEvenRowBackgroundHoveredBrush(TableRowHoveredBrush)

		.SetOddRowBackgroundBrush(TableRowNormalBrush)
		.SetOddRowBackgroundHoveredBrush(TableRowHoveredBrush)

		.SetSelectorFocusedBrush(TableRowSelectedBrush)

		.SetInactiveBrush(TableRowSelectedBrush)
		.SetInactiveHoveredBrush(TableRowSelectedBrush)

		.SetActiveBrush(TableRowSelectedBrush)
		.SetActiveHoveredBrush(TableRowSelectedBrush);
}

const FWeastLightStyle& FWeastLightStyle::GetDefault()
{
	static FWeastLightStyle Default;
	return Default;
}
