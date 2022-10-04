// Copyright Epic Games, Inc. All Rights Reserved.

#include "Styling/WeastStyle.h"

#include "Common/WeastCommon.h"

#include "Framework/Application/SlateApplication.h"

#include "Interfaces/IPluginManager.h"

//#include "Settings/WeastSettings.h"

#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/WeastWidgetStyle.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<const FCompositeFont> FWeastStyle::DefaultFont = NULL;

TSharedPtr<FSlateStyleSet> FWeastStyle::StyleInstance = nullptr;

void FWeastStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FWeastStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FWeastStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("WeastStyle"));
	return StyleSetName;
}

const FSlateBrush* FWeastStyle::GetBrush(FName InPropertyName, const ANSICHAR* InSpecifier)
{
	return StyleInstance->GetBrush(InPropertyName, InSpecifier);
}

TSharedRef<const FCompositeFont> FWeastStyle::GetDefaultFont()
{
	if (!DefaultFont.IsValid())
	{
		const FString ResourcesDir = IPluginManager::Get().FindPlugin("Weast")->GetBaseDir() / TEXT("Resources");

#define APPEND_FONT(TYPEFACE, NAME, FILENAME, HINTING) \
			(TYPEFACE).AppendFont(TEXT(NAME), ResourcesDir / TEXT("Fonts") / TEXT(FILENAME), HINTING, EFontLoadingPolicy::LazyLoad)

		TSharedRef<FCompositeFont> MutableDefaultFont = MakeShared<FStandaloneCompositeFont>();

		/// Default
		{
			APPEND_FONT(MutableDefaultFont->DefaultTypeface, "Regular", "MavenPro-Regular.ttf", EFontHinting::Default);

			APPEND_FONT(MutableDefaultFont->DefaultTypeface, "Medium", "MavenPro-Medium.ttf", EFontHinting::Default);

			APPEND_FONT(MutableDefaultFont->DefaultTypeface, "SemiBold", "MavenPro-SemiBold.ttf", EFontHinting::Default);

			APPEND_FONT(MutableDefaultFont->DefaultTypeface, "Bold", "MavenPro-Bold.ttf", EFontHinting::Default);
		}

		DefaultFont = MutableDefaultFont;

#undef APPEND_FONT
	}

	return DefaultFont.ToSharedRef();
}

FSlateFontInfo FWeastStyle::GetDefaultFontStyle(const FName InTypefaceFontName, const int32 InSize, const FFontOutlineSettings& InOutlineSettings)
{
	return FSlateFontInfo(GetDefaultFont(), InSize, InTypefaceFontName, InOutlineSettings);
}

const FSlateFontInfo FWeastStyle::GetFontStyle(FName InPropertyName, const ANSICHAR* InSpecifier)
{
	return StyleInstance->GetFontStyle(InPropertyName, InSpecifier);
}

const FVector2D Icon16x16(16.f, 16.f); // Size Specification : Small

const FVector2D Icon20x20(20.f, 20.f); // Size Specification : Normal

const FVector2D Icon40x40(40.f, 40.f); // Size Specification : Medium

const FVector2D Icon80x80(80.f, 80.f); // Size Specification : Large

const FVector2D Icon120x120(120.f, 120.f);  // Size Specification : Extra Large

const FVector2D Icon360x360(240.f, 240.f);  // Size Specification : XXL

TSharedRef< FSlateStyleSet > FWeastStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("WeastStyle"));

	//Get Path from IPluginManager to get the Config folder for the Model
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("Weast")->GetBaseDir() / TEXT("Resources"));

	// Toolkit
	Style->Set("Weast.Launch.Small", new IMAGE_BRUSH(TEXT("Toolkit/LaunchTabIcon_16x"), Icon16x16));
	Style->Set("Weast.Launch.Medium", new IMAGE_BRUSH(TEXT("Toolkit/LaunchButtonIcon_40x"), Icon40x40));

	//Dark icon Image
	Style->Set("Weast.Add.Dark.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Add"), Icon40x40));
	Style->Set("Weast.Bar.Dark.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Bar"), Icon16x16));
	Style->Set("Weast.Home.Dark.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Home"), Icon40x40));
	Style->Set("Weast.Info.Dark.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Info"), Icon40x40));
	Style->Set("Weast.Rain.Dark.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Rain"), Icon16x16));
	Style->Set("Weast.Wind.Dark.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Wind"), Icon16x16));
	Style->Set("Weast.BehindText.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/BehindText"), FMargin(4.f / 16.f)));
	Style->Set("Weast.Refresh.Dark.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Refresh"), Icon40x40));
	Style->Set("Weast.ButtonsPanel.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/ButtonsPanel"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.Favourite.Dark.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Favourite"), Icon40x40));
	Style->Set("Weast.Pin.Dark.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Pin"), Icon40x40));
	Style->Set("Weast.Location.Dark.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Location"), Icon20x20));
	Style->Set("Weast.Curve.Dark", new IMAGE_BRUSH(TEXT("SlateIcon/Dark/Curve"), FVector2D(120.0f / 30.0f)));

	//Button Dark
	Style->Set("Weast.ControlButtonHovered.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/ControlButtonHovered"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.ControlButtonPressed.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/ControlButtonPressed"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.PinnedButtonHoveredLeft.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/PinnedButtonHoveredLeft"), FMargin(4.f / 8.0f)));
	Style->Set("Weast.PinnedButtonHoveredRight.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/PinnedButtonHoveredRight"), FMargin(4.f / 8.0f)));
	Style->Set("Weast.PinnedButtonPressedLeft.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/PinnedButtonPressedLeft"), FMargin(4.f / 8.0f)));
	Style->Set("Weast.PinnedButtonPressedRight.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/PinnedButtonPressedRight"), FMargin(4.f / 8.0f)));

	//ListView/Border/Separator Dark
	Style->Set("Weast.TableRowActive.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/TableRowActive"), FMargin(1.0f)));
	Style->Set("Weast.TableRowHovered.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/TableRowHovered"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.TableRowSelected.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/TableRowSelected"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.Separator.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/Separator"), FMargin(1.0f / 4.0f)));
	Style->Set("Weast.PinnedBorder.Dark", new BOX_BRUSH(TEXT("SlateIcon/Dark/PinnedBorder"), FMargin(8.0f / 16.0f)));

	//Light icon Image
	Style->Set("Weast.Add.Light.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Add"), Icon40x40));
	Style->Set("Weast.Bar.Light.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Bar"), Icon16x16));
	Style->Set("Weast.Home.Light.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Home"), Icon40x40));
	Style->Set("Weast.Info.Light.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Info"), Icon40x40));
	Style->Set("Weast.Rain.Light.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Rain"), Icon16x16));
	Style->Set("Weast.Wind.Light.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Wind"), Icon16x16));
	Style->Set("Weast.BehindText.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/BehindText"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.Refresh.Light.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Refresh"), Icon40x40));
	Style->Set("Weast.ButtonsPanel.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/ButtonsPanel"), FMargin(4.f /16.0f)));
	Style->Set("Weast.Favourite.Light.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Favourite"), Icon40x40));
	Style->Set("Weast.Pin.Light.Medium", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Pin"), Icon40x40));
	Style->Set("Weast.Location.Light.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Location"), Icon20x20));
	Style->Set("Weast.Curve.Light", new IMAGE_BRUSH(TEXT("SlateIcon/Light/Curve"), FVector2D(120.f, 30.f)));


	//Button Light
	Style->Set("Weast.ControlButtonHovered.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/ControlButtonHovered"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.ControlButtonPressed.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/ControlButtonPressed"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.PinnedButtonHoveredLeft.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/PinnedButtonHoveredLeft"), FMargin(4.f / 8.0f)));
	Style->Set("Weast.PinnedButtonHoveredRight.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/PinnedButtonHoveredRight"), FMargin(4.f / 8.0f)));
	Style->Set("Weast.PinnedButtonPressedLeft.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/PinnedButtonPressedLeft"), FMargin(4.f / 8.0f)));
	Style->Set("Weast.PinnedButtonPressedRight.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/PinnedButtonPressedRight"), FMargin(4.f / 8.0f)));

	//ListView/Border/Separator Light
	Style->Set("Weast.TableRowActive.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/TableRowActive"), FMargin(1.0f)));
	Style->Set("Weast.TableRowHovered.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/TableRowHovered"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.TableRowSelected.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/TableRowSelected"), FMargin(4.f / 16.0f)));
	Style->Set("Weast.Separator.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/Separator"), FMargin(1.0f / 4.0f)));
	Style->Set("Weast.PinnedBorder.Light", new BOX_BRUSH(TEXT("SlateIcon/Light/PinnedBorder"), FMargin(8.0f / 16.0f)));

	//Sunrise Sunset Image
	Style->Set("Weast.Sunrise.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Sunrise"), Icon16x16));
	Style->Set("Weast.Sunset.Small", new IMAGE_BRUSH(TEXT("SlateIcon/Sunset"), Icon16x16));

	// Weather (Dark)
	//Style->Set("Weast.Weather.ChanceFlurries.Night.Light", new IMAGE_BRUSH_SVG(TEXT("Weather/Light/Night/chanceflurries"), Icon120x120));

	TArray<FWeatherDescriptorPtr> WeatherDescriptors;

	UE::Weast::FWeastCommon::GetWeatherDescriptors(WeatherDescriptors);


	//if (const UWeastSettings* WeastSettings = GetDefault<UWeastSettings>())
	//{

	//}

	for (const FWeatherDescriptorPtr WeatherDescriptorPtr : WeatherDescriptors)
	{
		{
			const FString CodeNameDarkSmall = FString::Printf(TEXT("Weast.Weather.%s.Dark.Small"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameDarkNormal = FString::Printf(TEXT("Weast.Weather.%s.Dark.Normal"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameDarkMedium = FString::Printf(TEXT("Weast.Weather.%s.Dark.Medium"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameDarkLarge = FString::Printf(TEXT("Weast.Weather.%s.Dark.Large"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameDarkExtraLarge = FString::Printf(TEXT("Weast.Weather.%s.Dark.ExtraLarge"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameDarkXXL = FString::Printf(TEXT("Weast.Weather.%s.Dark.XXL"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString PathNameDark = FString::Printf(TEXT("Weather/Dark/%s/%s"), *WeatherDescriptorPtr->GetTimeOfDay(), *WeatherDescriptorPtr->IconName.ToString());

			Style->Set(*CodeNameDarkSmall, new IMAGE_BRUSH(*PathNameDark, Icon16x16));
			Style->Set(*CodeNameDarkSmall, new IMAGE_BRUSH(*PathNameDark, Icon16x16));
			Style->Set(*CodeNameDarkNormal, new IMAGE_BRUSH(*PathNameDark, Icon20x20));
			Style->Set(*CodeNameDarkMedium, new IMAGE_BRUSH(*PathNameDark, Icon40x40));
			Style->Set(*CodeNameDarkLarge, new IMAGE_BRUSH(*PathNameDark, Icon80x80));
			Style->Set(*CodeNameDarkExtraLarge, new IMAGE_BRUSH(*PathNameDark, Icon120x120));
			Style->Set(*CodeNameDarkXXL, new IMAGE_BRUSH(*PathNameDark, Icon360x360));
		}

		{
			const FString CodeNameLightSmall = FString::Printf(TEXT("Weast.Weather.%s.Light.Small"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameLightNormal = FString::Printf(TEXT("Weast.Weather.%s.Light.Normal"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameLightMedium = FString::Printf(TEXT("Weast.Weather.%s.Light.Medium"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameLightLarge = FString::Printf(TEXT("Weast.Weather.%s.Light.Large"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameLightExtraLarge = FString::Printf(TEXT("Weast.Weather.%s.Light.ExtraLarge"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString CodeNameLightXXL = FString::Printf(TEXT("Weast.Weather.%s.Light.XXL"), *WeatherDescriptorPtr->CodeName.ToString());
			const FString PathNameLight = FString::Printf(TEXT("Weather/Light/%s/%s"), *WeatherDescriptorPtr->GetTimeOfDay(), *WeatherDescriptorPtr->IconName.ToString());

			Style->Set(*CodeNameLightSmall, new IMAGE_BRUSH(*PathNameLight, Icon16x16));
			Style->Set(*CodeNameLightNormal, new IMAGE_BRUSH(*PathNameLight, Icon20x20));
			Style->Set(*CodeNameLightMedium, new IMAGE_BRUSH(*PathNameLight, Icon40x40));
			Style->Set(*CodeNameLightLarge, new IMAGE_BRUSH(*PathNameLight, Icon80x80));
			Style->Set(*CodeNameLightExtraLarge, new IMAGE_BRUSH(*PathNameLight, Icon120x120));
			Style->Set(*CodeNameLightXXL, new IMAGE_BRUSH(*PathNameLight, Icon360x360));
		}
	}

	SetupDarkStyle(Style);

	SetupLightStyle(Style);

	return Style;
}

void FWeastStyle::SetupDarkStyle(TSharedRef<FSlateStyleSet> InStyle)
{
	FWeastDarkStyle WeastDarkStyle = FWeastDarkStyle();

	WeastDarkStyle.SetAddIconBrush(*InStyle->GetBrush("Weast.Add.Dark.Medium"))
		.SetBarIconBrush(*InStyle->GetBrush("Weast.Bar.Dark.Small"))
		.SetHomeIconBrush(*InStyle->GetBrush("Weast.Home.Dark.Medium"))
		.SetInfoIconBrush(*InStyle->GetBrush("Weast.Info.Dark.Medium"))
		.SetRainIconBrush(*InStyle->GetBrush("Weast.Rain.Dark.Small"))
		.SetWindIconBrush(*InStyle->GetBrush("Weast.Wind.Dark.Small"))
		.SetBehindTextIconBrush(*InStyle->GetBrush("Weast.BehindText.Dark"))
		.SetButtonsPanelIconBrush(*InStyle->GetBrush("Weast.ButtonsPanel.Dark"))
		.SetFavouriteIconBrush(*InStyle->GetBrush("Weast.Favourite.Dark.Medium"))
		.SetPinIconBrush(*InStyle->GetBrush("Weast.Pin.Dark.Medium"))
		.SetRefreshIconBrush(*InStyle->GetBrush("Weast.Refresh.Dark.Medium"))
		.SetLocationIconBrush(*InStyle->GetBrush("Weast.Location.Dark.Small"))
		.SetCurveIconBrush(*InStyle->GetBrush("Weast.Curve.Dark"))
	//Button
		.SetControlButtonHoveredIconBrush(*InStyle->GetBrush("Weast.ControlButtonHovered.Dark"))
		.SetControlButtonPressedIconBrush(*InStyle->GetBrush("Weast.ControlButtonPressed.Dark"))
		.SetPinnedButtonHoveredLeftIconBrush(*InStyle->GetBrush("Weast.PinnedButtonHoveredLeft.Dark"))
		.SetPinnedButtonHoveredRightIconBrush(*InStyle->GetBrush("Weast.PinnedButtonHoveredRight.Dark"))
		.SetPinnedButtonPressedLeftIconBrush(*InStyle->GetBrush("Weast.PinnedButtonPressedLeft.Dark"))
		.SetPinnedButtonPressedRightIconBrush(*InStyle->GetBrush("Weast.PinnedButtonPressedRight.Dark"))
	//Table/Border/Separator
		.SetTableRowActiveIconBrush(*InStyle->GetBrush("Weast.TableRowActive.Dark"))
		.SetTableRowHoveredIconBrush(*InStyle->GetBrush("Weast.TableRowHovered.Dark"))
		.SetTableRowSelectedIconBrush(*InStyle->GetBrush("Weast.TableRowSelected.Dark"))
		.SetSeparatorIconBrush(*InStyle->GetBrush("Weast.Separator.Dark"))
		.SetPinnedBorderIconBrush(*InStyle->GetBrush("Weast.PinnedBorder.Dark"));

	WeastDarkStyle.SetupButtonStyles();
	WeastDarkStyle.SetupTableRowStyles();
	WeastDarkStyle.SetupSearchBoxStyles();
	InStyle->Set("Weast.Theme.Dark", WeastDarkStyle);
}

void FWeastStyle::SetupLightStyle(TSharedRef<FSlateStyleSet> InStyle)
{
	FWeastLightStyle WeastLightStyle = FWeastLightStyle();

	WeastLightStyle.SetAddIconBrush(*InStyle->GetBrush("Weast.Add.Light.Medium"))
		.SetBarIconBrush(*InStyle->GetBrush("Weast.Bar.Light.Small"))
		.SetHomeIconBrush(*InStyle->GetBrush("Weast.Home.Light.Medium"))
		.SetInfoIconBrush(*InStyle->GetBrush("Weast.Info.Light.Medium"))
		.SetRainIconBrush(*InStyle->GetBrush("Weast.Rain.Light.Small"))
		.SetWindIconBrush(*InStyle->GetBrush("Weast.Wind.Light.Small"))
		.SetBehindTextIconBrush(*InStyle->GetBrush("Weast.BehindText.Light"))
		.SetButtonsPanelIconBrush(*InStyle->GetBrush("Weast.ButtonsPanel.Light"))
		.SetFavouriteIconBrush(*InStyle->GetBrush("Weast.Favourite.Light.Medium"))
		.SetPinIconBrush(*InStyle->GetBrush("Weast.Pin.Light.Medium"))
		.SetRefreshIconBrush(*InStyle->GetBrush("Weast.Refresh.Light.Medium"))
		.SetLocationIconBrush(*InStyle->GetBrush("Weast.Location.Light.Small"))
		.SetCurveIconBrush(*InStyle->GetBrush("Weast.Curve.Light"))
	//Button
		.SetControlButtonHoveredIconBrush(*InStyle->GetBrush("Weast.ControlButtonHovered.Light"))
		.SetControlButtonPressedIconBrush(*InStyle->GetBrush("Weast.ControlButtonPressed.Light"))
		.SetPinnedButtonHoveredLeftIconBrush(*InStyle->GetBrush("Weast.PinnedButtonHoveredLeft.Light"))
		.SetPinnedButtonHoveredRightIconBrush(*InStyle->GetBrush("Weast.PinnedButtonHoveredRight.Light"))
		.SetPinnedButtonPressedLeftIconBrush(*InStyle->GetBrush("Weast.PinnedButtonPressedLeft.Light"))
		.SetPinnedButtonPressedRightIconBrush(*InStyle->GetBrush("Weast.PinnedButtonPressedRight.Light"))
	//Table/Border/Separator
		.SetTableRowActiveIconBrush(*InStyle->GetBrush("Weast.TableRowActive.Light"))
		.SetTableRowHoveredIconBrush(*InStyle->GetBrush("Weast.TableRowHovered.Light"))
		.SetTableRowSelectedIconBrush(*InStyle->GetBrush("Weast.TableRowSelected.Light"))
		.SetSeparatorIconBrush(*InStyle->GetBrush("Weast.Separator.Light"))
		.SetPinnedBorderIconBrush(*InStyle->GetBrush("Weast.PinnedBorder.Light"));

	WeastLightStyle.SetupButtonStyles();
	WeastLightStyle.SetupTableRowStyles();
	WeastLightStyle.SetupSearchBoxStyles();
	InStyle->Set("Weast.Theme.Light", WeastLightStyle);
}

void FWeastStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FWeastStyle::Get()
{
	return *StyleInstance;
}
