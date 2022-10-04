// Copyright (c) 2022 Maurious Paul Vincent. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "WeastWidgetStyle.generated.h"

namespace EWeastView
{
	enum Orientation
	{
		EWVO_None,
		EWVO_Left,
		EWVO_Right,
		EWVO_Top,
		EWVO_Middle,
		EWVO_MiddleBottom,
		EWVO_Bottom,
		EWVO_LAST
	};

	enum Layout
	{
		EWVL_Home = 0,
		EWVL_Pinned = 1,
		EWVL_Info = 2
	};
}

struct FWeastViewArgsImages
{
public:

	FWeastViewArgsImages()
		: RainView(EWeastView::Orientation::EWVO_None)
		, PressureView(EWeastView::Orientation::EWVO_None)
		, WindView(EWeastView::Orientation::EWVO_None)
		, SunriseView(EWeastView::Orientation::EWVO_None)
		, SunsetView(EWeastView::Orientation::EWVO_None)
	{

	}

	FWeastViewArgsImages(EWeastView::Orientation InRainView,
		EWeastView::Orientation InPressureView,
		EWeastView::Orientation InWindView,
		EWeastView::Orientation InSunriseView,
		EWeastView::Orientation InSunsetView)
	{
		RainView = InRainView;
		PressureView = InPressureView;
		WindView = InWindView;
		SunriseView = InSunriseView;
		SunsetView = InSunsetView;
	}

public:
	TEnumAsByte<EWeastView::Orientation> RainView;
	TEnumAsByte<EWeastView::Orientation> PressureView;
	TEnumAsByte<EWeastView::Orientation> WindView;
	TEnumAsByte<EWeastView::Orientation> SunriseView;
	TEnumAsByte<EWeastView::Orientation> SunsetView;
};

struct FWeastViewArgs
{
public:
	FWeastViewArgs()
		: ImagesInfo(FWeastViewArgsImages())
	{

	}

	FWeastViewArgs(FWeastViewArgsImages InImagesInfo)

	{
		ImagesInfo = InImagesInfo;
	}

public:
	FWeastViewArgsImages ImagesInfo;
};

using FWeastViewArgsPtr = TSharedPtr<struct FWeastViewArgs>;
using FWeastViewArgsRef = TSharedRef<struct FWeastViewArgs>;

//TODO: Change the boolean, check the None of the enum instaed
class FViewArgsFactory
{
public:
	static FWeastViewArgsRef CreateHomeViewArgs()
	{

		static FWeastViewArgsImages HomeViewImagesInfoArgs = FWeastViewArgsImages(
			EWeastView::EWVO_Left,
			EWeastView::EWVO_Left,
			EWeastView::EWVO_Left,
			EWeastView::EWVO_Left,
			EWeastView::EWVO_Right
		);

		static FWeastViewArgsRef HomeViewArgs = MakeShared<FWeastViewArgs>(FWeastViewArgs(
			HomeViewImagesInfoArgs
		));
		return HomeViewArgs;
	}

	static FWeastViewArgsRef CreatePinnedViewArgs()
	{

		static FWeastViewArgsImages PinnedViewImagesInfoArgs = FWeastViewArgsImages(
			EWeastView::EWVO_Left,
			EWeastView::EWVO_None,
			 EWeastView::EWVO_Left,
			EWeastView::EWVO_None,
			EWeastView::EWVO_None
		);

		static FWeastViewArgsRef PinnedViewArgs = MakeShared<FWeastViewArgs>(FWeastViewArgs(
			PinnedViewImagesInfoArgs
		));
		return PinnedViewArgs;
	}

	static FWeastViewArgsRef CreateInfoCurrentViewArgs()
	{
		static FWeastViewArgsImages InfoCurrentViewImagesInfoArgs = FWeastViewArgsImages(
			EWeastView::EWVO_Left,
			EWeastView::EWVO_Left,
			EWeastView::EWVO_Left,
			EWeastView::EWVO_None,
			EWeastView::EWVO_None
		);

		static FWeastViewArgsRef InfoCurrentViewArgs = MakeShared<FWeastViewArgs>(FWeastViewArgs(
			InfoCurrentViewImagesInfoArgs
		));
		return InfoCurrentViewArgs;
	}
};

/**
 * Widget style representing the common theme.
 */

using FWeastWidgetStylePtr = TSharedPtr<struct FWeastWidgetStyle>;

using FWeastWidgetStyleRef = TSharedRef<struct FWeastWidgetStyle>;

USTRUCT()
struct FWeastWidgetStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

		FWeastWidgetStyle();

	virtual ~FWeastWidgetStyle();

	//~ BEGIN : FSlateWidgetStyle Interface

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	virtual const FName GetTypeName() const override;

	//~ END : FSlateWidgetStyle Interface

	/**
	 * Implementation(s)
	 */
	virtual const FString GetStyleName() const;

	static const FWeastWidgetStyle& GetDefault();

	static const FWeastWidgetStyle* GetCurrentStyle();

	//Content
	FWeastWidgetStyle& SetContentAreaBrush(const FSlateBrush& InContentAreaBrush) { ContentAreaBrush = InContentAreaBrush; return *this; }

	//Images
	FWeastWidgetStyle& SetAddIconBrush(const FSlateBrush& InAddIconBrush) { AddIconBrush = InAddIconBrush; return *this; }
	FWeastWidgetStyle& SetBarIconBrush(const FSlateBrush& InBarIconBrush) { PressureIconBrush = InBarIconBrush; return *this; }
	FWeastWidgetStyle& SetHomeIconBrush(const FSlateBrush& InHomeIconBrush) { HomeIconBrush = InHomeIconBrush; return *this; }
	FWeastWidgetStyle& SetInfoIconBrush(const FSlateBrush& InInfoIconBrush) { InfoIconBrush = InInfoIconBrush; return *this; }
	FWeastWidgetStyle& SetRainIconBrush(const FSlateBrush& InRainIconBrush) { RainIconBrush = InRainIconBrush; return *this; }
	FWeastWidgetStyle& SetWindIconBrush(const FSlateBrush& InWindIconBrush) { WindIconBrush = InWindIconBrush; return *this; }
	FWeastWidgetStyle& SetBehindTextIconBrush(const FSlateBrush& InBehindTextIconBrush) { BehindTextIconBrush = InBehindTextIconBrush; return *this; }
	FWeastWidgetStyle& SetFavouriteIconBrush(const FSlateBrush& InFavouriteIconBrush) { FavouriteIconBrush = InFavouriteIconBrush; return *this; }
	FWeastWidgetStyle& SetPinIconBrush(const FSlateBrush& InPinIconBrush) { PinIconBrush = InPinIconBrush; return *this; }
	FWeastWidgetStyle& SetRefreshIconBrush(const FSlateBrush& InRefreshIconBrush) { RefreshIconBrush = InRefreshIconBrush; return *this; }
	FWeastWidgetStyle& SetLocationIconBrush(const FSlateBrush& InLocationIconBrush) { LocationIconBrush = InLocationIconBrush; return *this; }
	FWeastWidgetStyle& SetCurveIconBrush(const FSlateBrush& InCurveIconBrush) { CurveIconBrush = InCurveIconBrush; return *this; }

	//Button
	FWeastWidgetStyle& SetButtonsPanelIconBrush(const FSlateBrush& InButtonsPanelIconBrush) { ButtonsPanelIconBrush = InButtonsPanelIconBrush; return *this; }
	FWeastWidgetStyle& SetControlButtonHoveredIconBrush(const FSlateBrush& InControlButtonHoveredIconBrush) { ControlButtonHoveredIconBrush = InControlButtonHoveredIconBrush; return *this; }
	FWeastWidgetStyle& SetPinnedButtonHoveredLeftIconBrush(const FSlateBrush& InPinnedButtonHoveredLeftIconBrush) { PinnedButtonHoveredLeftIconBrush = InPinnedButtonHoveredLeftIconBrush; return *this; }
	FWeastWidgetStyle& SetPinnedButtonHoveredRightIconBrush(const FSlateBrush& InPinnedButtonHoveredRightIconBrush) { PinnedButtonHoveredRightIconBrush = InPinnedButtonHoveredRightIconBrush; return *this; }
	FWeastWidgetStyle& SetPinnedButtonPressedLeftIconBrush(const FSlateBrush& InPinnedButtonPressedLeftIconBrush) { PinnedButtonPressedLeftIconBrush = InPinnedButtonPressedLeftIconBrush; return *this; }
	FWeastWidgetStyle& SetControlButtonPressedIconBrush(const FSlateBrush& InControlButtonPressedIconBrush) { ControlButtonPressedIconBrush = InControlButtonPressedIconBrush; return *this; }
	FWeastWidgetStyle& SetPinnedButtonPressedRightIconBrush(const FSlateBrush& InPinnedButtonPressedRightIconBrush) { PinnedButtonPressedRightIconBrush = InPinnedButtonPressedRightIconBrush; return *this; }

	//Table/Border/Separator/ Curve
	FWeastWidgetStyle& SetTableRowActiveIconBrush(const FSlateBrush& InTableRowNormalBrush) { TableRowNormalBrush = InTableRowNormalBrush; return *this; }
	FWeastWidgetStyle& SetTableRowHoveredIconBrush(const FSlateBrush& InTableRowHoveredBrush) { TableRowHoveredBrush = InTableRowHoveredBrush; return *this; }
	FWeastWidgetStyle& SetTableRowSelectedIconBrush(const FSlateBrush& InTableRowSelectedBrush) { TableRowSelectedBrush = InTableRowSelectedBrush; return *this; }
	FWeastWidgetStyle& SetSeparatorIconBrush(const FSlateBrush& InSeparatorBrush) { SeparatorBrush = InSeparatorBrush; return *this; }
	FWeastWidgetStyle& SetPinnedBorderIconBrush(const FSlateBrush& InPinnedBorderBrush) { PinnedBorderBrush = InPinnedBorderBrush; return *this; }


	/**
	* Initializes Table styles.
	*/
	virtual void SetupTableRowStyles();

	/**
	* Initializes button styles.
	*/
	virtual void SetupButtonStyles();

	/**
	* Initializes button styles.
	*/
	virtual void SetupSearchBoxStyles();

protected:

	/**
	 * Initializes brush styles.
	 */
	//virtual void SetupBrushStyles();

	/**
	 * Initializes text styles.
	 */
	virtual void SetupTextStyles();

	/**
	* Initializes Color styles.
	*/
	virtual void SetupColorStyles();


private:

	/**
	 * Attribute(s)
	 */

public:

	/**
	 * Brush Styles
	 */

	 /** Brush used by the Weast Panels to draw the content associated with this panel. */
	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush ContentAreaBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush AddIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush PressureIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush HomeIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush InfoIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush RainIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush WindIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush BehindTextIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush ButtonsPanelIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush FavouriteIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush PinIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush RefreshIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush LocationIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush CurveIconBrush;


	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush ControlButtonHoveredIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush ControlButtonPressedIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush PinnedButtonHoveredLeftIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush PinnedButtonHoveredRightIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush PinnedButtonPressedLeftIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush PinnedButtonPressedRightIconBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush SeparatorBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush PinnedBorderBrush;

	/**
	 * Text Styles
	 */

	 /** Body Text Style */
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle BodyTextStyle;

	/** Caption Text Style */
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle CaptionTextStyle;

	/** Subtitle Text Style */
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle SubtitleTextStyle;

	/** Title Text Style */
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle TitleTextStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FTableRowStyle TableRowViewStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush TableRowNormalBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush TableRowHoveredBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush TableRowSelectedBrush;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FTableViewStyle TableViewStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSearchBoxStyle SearchBoxStyle;

	/**
	* Text Color
	*/

	UPROPERTY(EditAnywhere, Category = Appearance)
		FLinearColor TextColor;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FLinearColor BackgroundColor;

	/**
	* Button Style
	*/

	UPROPERTY(EditAnywhere, Category = Appearance)
		FButtonStyle ButtonLeftStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FButtonStyle ButtonRightStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FButtonStyle ButtonControlStyle;

private:

	/** Holds the name of this slate widget style type. */
	static const FName TypeName;

	static const FString StyleName;
};

/**
 * Widget style representing the dark theme.
 */
USTRUCT()
struct FWeastDarkStyle : public FWeastWidgetStyle
{
	GENERATED_USTRUCT_BODY()

public:

	FWeastDarkStyle();

	virtual ~FWeastDarkStyle();

	//~ BEGIN : FSlateWidgetStyle Interface

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	virtual const FName GetTypeName() const override;

	virtual const FString GetStyleName() const override;

	//~ END : FSlateWidgetStyle Interface

	//~ BEGIN : FWeastWidgetStyle Interface

	virtual void SetupButtonStyles() override;

	virtual void SetupTableRowStyles() override;

	virtual void SetupSearchBoxStyles() override;
protected:

	//virtual void SetupBrushStyles() override;

	virtual void SetupTextStyles() override;

	virtual void SetupColorStyles() override;


	//~ END : FWeastWidgetStyle Interface

	/**
	 * Implementation(s)
	 */

public:

	static const FWeastDarkStyle& GetDefault();
public:
	/**
	 * Attribute(s)
	 */
	 /** Holds the name of this slate widget style type. */
	static const FName TypeName;

	static const FString StyleName;
};

/**
 * Widget style representing the dark theme.
 */
USTRUCT()
struct FWeastLightStyle : public FWeastWidgetStyle
{
	GENERATED_USTRUCT_BODY()

		FWeastLightStyle();

	virtual ~FWeastLightStyle();

	//~ BEGIN : FSlateWidgetStyle Interface

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	virtual const FName GetTypeName() const override;

	virtual const FString GetStyleName() const override;

	//~ END : FSlateWidgetStyle Interface

	//~ BEGIN : FWeastWidgetStyle Interface

	virtual void SetupButtonStyles() override;

	virtual void SetupTableRowStyles() override;

	virtual void SetupSearchBoxStyles() override;
protected:

	//virtual void SetupBrushStyles() override;

	virtual void SetupTextStyles() override;

	virtual void SetupColorStyles() override;


	//~ END : FWeastWidgetStyle Interface

	/**
	 * Implementation(s)
	 */

public:
	static const FWeastLightStyle& GetDefault();

	/**
	 * Attribute(s)
	 */
	 /** Holds the name of this slate widget style type. */
	static const FName TypeName;

	static const FString StyleName;
};
