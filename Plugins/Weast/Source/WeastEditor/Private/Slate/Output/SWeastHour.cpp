
#include "Slate/Output/SWeastHour.h"

#include "Components/VerticalBox.h"
#include "Slate/Public/SlateOptMacros.h"
#include "Styling/WeastStyle.h"

#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSeparator.h"

#define LOCTEXT_NAMESPACE "SWeastHour"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastHour::Construct(const FArguments& InArgs, const IWeastModelRef& InModel)
{
	Model = InModel;
	CityGuid = InArgs._CityGuid.Get();
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();
	ImageSize = InArgs._ImageSize.Get();
	Hour = InArgs._Hour.Get();

	ChildSlot
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.Padding(0.f, 8.f, 0.f, 20.f)
			[
				SNew(SBox)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.WidthOverride(60.f)
				[
					SNew(STextBlock)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Font(WeastStyle->CaptionTextStyle.Font)
					.Text_Lambda([this]()
					{
						if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetCityById(CityGuid).IsValid())
						{
							return Model->GetCityById(CityGuid)->GetHour(Hour);
						}
						return FText::GetEmpty();
					})
				]
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.Padding(0.f, 10.f)
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SImage)
					.Image_Lambda([this]()
					{
						return FWeastStyle::Get().GetBrush(GetWeatherDescriptorStyleName(WeastStyle->GetStyleName(), ImageSize));
					})
				]
			]
			+ SVerticalBox::Slot()
			.Padding(0.f, 20.f, 0.f, 8.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Bottom)
				[
					SNew(STextBlock)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Font(WeastStyle->CaptionTextStyle.Font)
					.Text_Lambda([this]()
					{
							if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetCityById(CityGuid).IsValid())
							{
								const FText Max = FText::FromString(FString::FromInt(Model->GetCityById(CityGuid)->GetHourlyTemp(Hour)));
								return FText::Format(LOCTEXT("Temperature", "{0}{1}"), Max, GetTemperatureUnit());
							}
							return FText::GetEmpty();
					})
				]
			]
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FName SWeastHour::GetWeatherDescriptorStyleName(FString InStyleName, FString InSize) const
{
	FName DescriptorStyleName = FName(TEXT(""));
	if (Model.IsValid() && Model->HasFinishedLoading())
	{
		if (Model->GetCityById(CityGuid).IsValid())
		{
			DescriptorStyleName = UE::Weast::FWeastCommon::GetWeatherDescriptorStyleName(
				Model->GetCityById(CityGuid)->hourly[Hour].weather.id,
				FName(Model->GetCityById(CityGuid)->hourly[Hour].weather.icon),
				InStyleName,
				InSize);
		}
	}
	return DescriptorStyleName;
}

FText SWeastHour::GetTemperatureUnit() const
{
	{
		FText Unit = LOCTEXT("UnitFormat", "°C");
		if (const UWeastSettings* WeastSettings = GetDefault<UWeastSettings>())
		{
			switch (WeastSettings->GetTemperatureUnit())
			{
			case ETemperature::ETU_Fahrenheit:
				Unit = LOCTEXT("UnitFormat", "°F");
				break;

			case ETemperature::ETU_Kelvin:
				Unit = LOCTEXT("UnitFormat", "°K");
				break;

			case ETemperature::ETU_Celsius:
			default:
				break;
			}
		}
		return Unit;
	}
}

#undef LOCTEXT_NAMESPACE