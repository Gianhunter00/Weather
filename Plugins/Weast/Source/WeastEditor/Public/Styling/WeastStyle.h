// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

/**
 * Custom styling for Weast Plugin.
 */
class FWeastStyle
{
	/**
	 * Implementation(s)
	 */

public:

    /**
     * Static implementation that initializes the slate resources.
     */
	static void Initialize();

    /**
     * Static implementation that tears down the loaded slate resources.
     */
	static void Shutdown();

	/**
     * Reloads textures used by slate renderer.
     */
	static void ReloadTextures();

	/**
     * Retrieves the Slate style set instance.
     * 
     * @return The Slate style set.
     */
	static const ISlateStyle& Get();

    /**
     * Retrieves the name of this slate style.
     * 
     * @return The Slate style name.
     */
	static FName GetStyleSetName();

    /**
     * Retrieves the slate brush specified by the given name and specification.
     * 
     * @param InPropertyName The name of the slate resource.
     * @param InSpecifier The size specification of the same.
     * 
     * @return The slate resource if found, nullptr otherwise.
     */
    static const FSlateBrush* GetBrush(FName InPropertyName, const ANSICHAR* InSpecifier = NULL);

    /**
     * Populates the default font style set.
     * 
     * @return The composite of all available font styles.
     */
    static TSharedRef<const FCompositeFont> GetDefaultFont();

    /**
     * Retrieves the specified typeface from the default font (if available).
     * Supported Typefaces : Regular, Medium, SemiBold, Bold.
     * 
     * @param InTypefaceFontName Typeface of the font.
     * @param InSize Size of the font.
     * @param InOutlineSettings Optional outline settings.
     * 
     * @return The typeface from the default font.
     */
    static FSlateFontInfo GetDefaultFontStyle(const FName InTypefaceFontName, const int32 InSize, const FFontOutlineSettings& InOutlineSettings = FFontOutlineSettings());

    /**
     * Retrieves the slate font specified by the given name and specification.
     * 
     * @param InPropertyName The name of the slate font resource.
     * @param InSpecifier The size specification of the same.
     * 
     * @return The slate resource if found, nullptr otherwise.
     */
    static const FSlateFontInfo GetFontStyle(FName InPropertyName, const ANSICHAR* InSpecifier = NULL);

private:

    /**
     * Static implementation that creates this slate style from scratch.
     * 
     * @return The singleton instance of this style.
     */
	static TSharedRef< class FSlateStyleSet > Create();


    static void SetupDarkStyle(TSharedRef<FSlateStyleSet> InStyle);


    static void SetupLightStyle(TSharedRef<FSlateStyleSet> InStyle);

	/**
	 * Attribute(s)
	 */

private:

    /**
     * Holds a shared pointer to the singleton instance of default font.
     */
    static TSharedPtr<const FCompositeFont> DefaultFont;

    /**
     * Holds a shared pointer to the singleton instance of this style.
     */
	static TSharedPtr< class FSlateStyleSet > StyleInstance;

};