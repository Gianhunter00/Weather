
#include "Slate/Panels/SWeastInfoImagePanel.h"

#include "Components/HorizontalBox.h"
#include "Slate/Output/SWeastImageWithText.h"
#include "SlateOptMacros.h"
#include "Styling/WeastStyle.h"

#define LOCTEXT_NAMESPACE "SWeastInfoImagePanel"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastInfoImagePanel::Construct(const FArguments& InArgs, const FWeastViewArgsImages& InViewType, const IWeastModelRef& InModel)
{
	CityGuid = InArgs._CityGuid.Get();
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();
	WeastView = InViewType;
	UseActiveCity = InArgs._bUseActiveCity;
	Model = InModel;

	const TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);
	const TSharedPtr<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);

	if(WeastView.RainView != EWeastView::EWVO_None)
	{
		HorizontalBox->AddSlot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SWeastImageWithText)
				.ImageOrientation(WeastView.RainView)
				.Text(this, &SWeastInfoImagePanel::GetRainTextData)
				.Font(WeastStyle->BodyTextStyle.Font)
				.TextColor(WeastStyle->TextColor)
				.Image(&WeastStyle->RainIconBrush)
			];
	}

	if (WeastView.PressureView != EWeastView::EWVO_None)
	{
		HorizontalBox->AddSlot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SWeastImageWithText)
				.ImageOrientation(WeastView.PressureView)
				.Text(this, &SWeastInfoImagePanel::GetPressureTextData)
				.Font(WeastStyle->BodyTextStyle.Font)
				.TextColor(WeastStyle->TextColor)
				.Image(&WeastStyle->PressureIconBrush)
			];
	}

	if (WeastView.WindView != EWeastView::EWVO_None)
	{
		HorizontalBox->AddSlot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SWeastImageWithText)
				.ImageOrientation(WeastView.WindView)
				.Text(this, &SWeastInfoImagePanel::GetWindSpeedTextData)
				.Font(WeastStyle->BodyTextStyle.Font)
				.TextColor(WeastStyle->TextColor)
				.Image(&WeastStyle->WindIconBrush)
			];
	}
	if(HorizontalBox->NumSlots() > 0)
	{
		VerticalBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(0.f,0.f,0.f,5.f)
			.AutoHeight()
			[
				HorizontalBox.ToSharedRef()
			];
	}
	if (WeastView.SunriseView != EWeastView::EWVO_None && 
		WeastView.SunsetView != EWeastView::EWVO_None)
	{
		VerticalBox->AddSlot()
			.Padding(4.f, 4.f)
			.AutoHeight()
			[
				//Sunrise
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(4.f, 4.f, 4.f, 5.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					[
					SNew(SWeastImageWithText)
					.ImageOrientation(WeastView.SunriseView)
					.Text(this, &SWeastInfoImagePanel::GetSunriseTextData)
					.Font(WeastStyle->BodyTextStyle.Font)
					.TextColor(WeastStyle->TextColor)
					.Image(FWeastStyle::Get().GetBrush("Weast.Sunrise.Small"))
					]
				]
				+ SVerticalBox::Slot()
				[
					//Curve
					SNew(SOverlay)
					+SOverlay::Slot()
					.Padding(0.f, 4.f, 0.f, 0.f)
					[
						SNew(SImage)
						.Image(&WeastStyle->CurveIconBrush)
					]
					//Sunset
					+ SOverlay::Slot()
					.Padding(4.f, 0.f, 4.f, 10.f)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.HAlign(HAlign_Right)
						[
							SNew(SWeastImageWithText)
							.ImageOrientation(WeastView.SunsetView)
							.Text(this, &SWeastInfoImagePanel::GetSunsetTextData)
							.Font(WeastStyle->BodyTextStyle.Font)
							.TextColor(WeastStyle->TextColor)
							.Image(FWeastStyle::Get().GetBrush("Weast.Sunset.Small"))
						]
					]
				]
			];
	}
	else
	{
		if (WeastView.SunriseView != EWeastView::EWVO_None)
		{
			VerticalBox->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(4.f, 4.f)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Fill)
					[
						SNew(SWeastImageWithText)
						.ImageOrientation(WeastView.SunriseView)
						.Text(this, &SWeastInfoImagePanel::GetSunriseTextData)
						.Font(WeastStyle->BodyTextStyle.Font)
						.TextColor(WeastStyle->TextColor)
						.Image(FWeastStyle::Get().GetBrush("Weast.Sunrise.Small"))
					]
				];
		}
		if (WeastView.SunsetView != EWeastView::EWVO_None)
		{
			VerticalBox->AddSlot()
				.Padding(4.f, 4.f)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Right)
					[
						SNew(SWeastImageWithText)
						.ImageOrientation(WeastView.SunsetView)
						.Text(this, &SWeastInfoImagePanel::GetSunsetTextData)
						.Font(WeastStyle->BodyTextStyle.Font)
						.TextColor(WeastStyle->TextColor)
						.Image(FWeastStyle::Get().GetBrush("Weast.Sunset.Small"))
					]
				];
		}
	}

	ChildSlot
		[
			VerticalBox.ToSharedRef()
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FText SWeastInfoImagePanel::BuildValueText(FString InText, FString InUnit) const
{
	return FText::Format(LOCTEXT("TextValueData", "{0}{1}"), FText::FromString(InText), FText::FromString(InUnit));
}

FText SWeastInfoImagePanel::BuildValueText(FText InText, FString InUnit) const
{
	return FText::Format(LOCTEXT("TextValueData", "{0}{1}"),InText, FText::FromString(InUnit));
}

FText SWeastInfoImagePanel::GetRainTextData() const
{
	if (Model.IsValid() && Model->HasFinishedLoading())
	{
		if (UseActiveCity.Get() && Model->GetActiveCity().IsValid())
		{
			return BuildValueText(FString::FromInt(Model->GetActiveCity()->GetPrecipitationProbabilityByDay()), TEXT("%"));
		}
		else if (Model->GetCityById(CityGuid).IsValid())
		{
			return BuildValueText(FString::FromInt(Model->GetCityById(CityGuid)->GetPrecipitationProbabilityByDay()), TEXT("%"));
		}
	}
	return LOCTEXT("RainData", "RainDataError");
}

FText SWeastInfoImagePanel::GetPressureTextData() const
{
	if (Model.IsValid() && Model->HasFinishedLoading())
	{
		if (UseActiveCity.Get() && Model->GetActiveCity().IsValid())
		{
			return BuildValueText(FString::FromInt(Model->GetActiveCity()->GetPressure()), TEXT("mBar"));
		}
		else if (Model->GetCityById(CityGuid).IsValid())
		{
			return BuildValueText(FString::FromInt(Model->GetCityById(CityGuid)->GetPressure()), TEXT("mBar"));
		}
	}
	return LOCTEXT("PressureData", "PressureDataError");
}

FText SWeastInfoImagePanel::GetWindSpeedTextData() const
{
	if (Model.IsValid() && Model->HasFinishedLoading())
	{
		if (UseActiveCity.Get() && Model->GetActiveCity().IsValid())
		{
			return BuildValueText(FString::FromInt(Model->GetActiveCity()->GetWindSpeed()), TEXT("m/s"));
		}
		else if (Model->GetCityById(CityGuid).IsValid())
		{
			return BuildValueText(FString::FromInt(Model->GetCityById(CityGuid)->GetWindSpeed()), TEXT("m/s"));
		}
	}
	return LOCTEXT("WindSpeedData", "WindSpeedDataError");
}

FText SWeastInfoImagePanel::GetSunriseTextData() const
{
	if (Model.IsValid() && Model->HasFinishedLoading())
	{
		if (UseActiveCity.Get() && Model->GetActiveCity().IsValid())
		{
			return BuildValueText(Model->GetActiveCity()->GetSunrise());
		}
		else if (Model->GetCityById(CityGuid).IsValid())
		{
			return BuildValueText(Model->GetCityById(CityGuid)->GetSunrise());
		}
	}
	return LOCTEXT("SunriseData", "SunriseDataError");
}

FText SWeastInfoImagePanel::GetSunsetTextData() const
{
	if (Model.IsValid() && Model->HasFinishedLoading())
	{
		if (UseActiveCity.Get() && Model->GetActiveCity().IsValid())
		{
			return BuildValueText(Model->GetActiveCity()->GetSunset());
		}
		else if (Model->GetCityById(CityGuid).IsValid())
		{
			return BuildValueText(Model->GetCityById(CityGuid)->GetSunset());
		}
	}
	return LOCTEXT("SunsetData", "SunsetDataError");
}

#undef LOCTEXT_NAMESPACE
