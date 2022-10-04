
#include "Slate/Output/SWeastDay.h"

#include "Components/VerticalBox.h"
#include "Slate/Public/SlateOptMacros.h"
#include "Styling/WeastStyle.h"

#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSeparator.h"

#define LOCTEXT_NAMESPACE "SWeastDay"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastDay::Construct(const FArguments& InArgs, const IWeastModelRef& InModel)
{
	Model = InModel;
	CityGuid = InArgs._CityGuid.Get();
	DayAfterThis = InArgs._DayAfterThis.Get();
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();
	ImageSize = InArgs._ImageSize.Get();

	ChildSlot
		[
			SNew(SHorizontalBox)

			+SHorizontalBox::Slot()
			.FillWidth(0.33f)
			.Padding(10.f, 0.f, 0.f, 0.f)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Font(WeastStyle->CaptionTextStyle.Font)
					.Text_Lambda([this]()
					{
						if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetCityById(CityGuid).IsValid())
						{
							return Model->GetCityById(CityGuid)->GetDay(DayAfterThis);
						}
						return FText::GetEmpty();
					})
				]
			]

			+ SHorizontalBox::Slot()
			[
				SNew(SBox)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					//GetImageOfDay
					SNew(SImage)
					.Image_Lambda([this]()
						{
							return FWeastStyle::Get().GetOptionalBrush(GetWeatherDescriptorStyleName(WeastStyle->GetStyleName(), ImageSize));
						})
				]
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.AutoWidth()
			.Padding(2.f)
			[
					SNew(STextBlock)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Font(WeastStyle->CaptionTextStyle.Font)
					.Text_Lambda([this]()
					{
							if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetCityById(CityGuid).IsValid())
							{
								const FText Max = FText::FromString(FString::FromInt(Model->GetCityById(CityGuid)->GetMaxDailyTemp(DayAfterThis)));
								return FText::Format(LOCTEXT("MaxTemperature", "{0}{1}"), Max, GetTemperatureUnit());
							}
							return FText::GetEmpty();
					})
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.AutoWidth()
			.Padding(4.f)
			[
				SNew(STextBlock)
				.ColorAndOpacity(WeastStyle->TextColor)
				.Font(WeastStyle->BodyTextStyle.Font)
				.Text_Lambda([this]()
				{
						if (Model.IsValid() && Model->HasFinishedLoading() &&  Model->GetCityById(CityGuid).IsValid())
						{
							const FText Min = FText::FromString(FString::FromInt(Model->GetCityById(CityGuid)->GetMinDailyTemp(DayAfterThis)));
							return FText::Format(LOCTEXT("MinTemperature", "{0}{1}"), Min, GetTemperatureUnit());
						}
						return FText::GetEmpty();
				})
			]
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FName SWeastDay::GetWeatherDescriptorStyleName(FString InStyleName, FString InSize) const
{
	FName DescriptorStyleName = FName(TEXT(""));
	if (Model.IsValid() && Model->HasFinishedLoading())
	{
		if (Model->GetCityById(CityGuid).IsValid())
		{
			DescriptorStyleName = UE::Weast::FWeastCommon::GetWeatherDescriptorStyleName(
				Model->GetCityById(CityGuid)->daily[DayAfterThis].weather.id,
				FName(Model->GetCityById(CityGuid)->daily[DayAfterThis].weather.icon),
				InStyleName,
				InSize);
		}
	}
	return DescriptorStyleName;
}

FText SWeastDay::GetTemperatureUnit() const
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
