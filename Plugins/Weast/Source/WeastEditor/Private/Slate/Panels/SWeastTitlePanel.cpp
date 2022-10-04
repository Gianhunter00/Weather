#include "Slate/Panels/SWeastTitlePanel.h"

#include "Components/HorizontalBox.h"
#include "Slate/Output/SWeastImageWithText.h"
#include "SlateOptMacros.h"
#include "Styling/WeastStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

#define LOCTEXT_NAMESPACE "SWeastTitlePanel"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeastTitlePanel::Construct(const FArguments& InArgs, const IWeastModelRef& InModel)
{
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();
	ImageSize = InArgs._ImageSize.Get();
	Model = InModel;
	CityGuid = InArgs._CityGuid.Get();

	if(!CityGuid.IsValid())
	{
		if (Model->GetActiveCity().IsValid())
		{
			CityGuid = Model->GetActiveCityId();
		}
	}

	ChildSlot
		[
			SNew(SWidgetSwitcher)
			.WidgetIndex(InArgs._WidgetIndex.Get())

			// 0 = HomeLayout
			+SWidgetSwitcher::Slot()
			[
				BuildHomeLayout()
			]

			// 1 = Pinned
			+ SWidgetSwitcher::Slot()
			[
				BuildPinnedLayout()
			]

			// 2 = Info
			+ SWidgetSwitcher::Slot()
			[
				BuildInfoLayout()
			]
		];
}

TSharedRef<SWidget> SWeastTitlePanel::BuildInfoLayout() const
{
	return SNew(SHorizontalBox)

			+SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(0.f, 10.f, 0.f, 4.f)
			[
				//City
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.WrapTextAt(250.f)
						.Font(WeastStyle->SubtitleTextStyle.Font)
						.ColorAndOpacity(WeastStyle->TextColor)
						.Text_Lambda([this]()
						{
								if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetActiveCity().IsValid())
								{
									return FText::Format(LOCTEXT("CityText", "{0}"), FText::FromString(Model->GetActiveCity()->City));
								}
								return FText::GetEmpty();
						})
					]
				]
					
				//Temperature
				+ SVerticalBox::Slot()
				.Padding(0.f, 4.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(WeastStyle->TitleTextStyle.Font)
						.ColorAndOpacity(WeastStyle->TextColor)
						.Text_Lambda([this]()
						{
								if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetActiveCity().IsValid())
								{
									return FText::Format(LOCTEXT("TemperatureText", "{0}{1}"), Model->GetActiveCity()->GetTemperature(), GetTemperatureUnit());
								}
								return FText::GetEmpty();
						})
					]
				]
				//WeatherType
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				.Padding(0.f, 4.f)
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SNew(SBorder)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Padding(4.f)
						.BorderImage(&WeastStyle->BehindTextIconBrush)
						[
							SNew(STextBlock)
							.WrapTextAt(250.f)
							.Font(WeastStyle->CaptionTextStyle.Font)
							.ColorAndOpacity(WeastStyle->TextColor)
							.Text_Lambda([this]()
							{
									if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetActiveCity().IsValid())
									{
										return FText::Format(LOCTEXT("InfoText", " {0} "), FText::FromString(Model->GetActiveCity()->GetDescription().ToUpper()));
									}
									return FText::GetEmpty();
							})
						]
					]
				]
			]
			//Image
			+ SHorizontalBox::Slot()
			.Padding(4.f, 10.f, 4.f, 4.f)
			.AutoWidth()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.AutoHeight()
				[
					SNew(SImage)
					.Image_Lambda([this]()
						{
							return FWeastStyle::Get().GetBrush(GetWeatherDescriptorStyleName(WeastStyle->GetStyleName(), ImageSize, true));
						})
				]
			];
}

TSharedRef<SWidget> SWeastTitlePanel::BuildPinnedLayout() const
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		[
			SNew(SVerticalBox)

			//Temperature
			+ SVerticalBox::Slot()
			.Padding(2.f)
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Font(WeastStyle->TitleTextStyle.Font)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Text_Lambda([this]()
					{
							if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetCityById(CityGuid).IsValid())
							{
								return FText::Format(LOCTEXT("TemperatureText", "{0}{1}"), Model->GetCityById(CityGuid)->GetTemperature(), GetTemperatureUnit());
							}
							return FText::GetEmpty();
					})
				]
			]
			//City
			+ SVerticalBox::Slot()
			.Padding(2.f)
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Font(WeastStyle->BodyTextStyle.Font)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Text_Lambda([this]()
					{
							if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetCityById(CityGuid).IsValid())
							{
								return FText::Format(LOCTEXT("CityText", "{0}"), FText::FromString(Model->GetCityById(CityGuid)->City));
							}
							return FText::GetEmpty();
					})
				]
			]

			//Region
			+ SVerticalBox::Slot()
			.Padding(2.f)
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Font(WeastStyle->CaptionTextStyle.Font)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Text_Lambda([this]()
					{
							if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetCityById(CityGuid).IsValid())
							{
								return FText::Format(LOCTEXT("RegionText", "{0}"), FText::FromString(Model->GetCityById(CityGuid)->Region));
							}
							return FText::GetEmpty();
					})
				]
			]
		]
		//Image
		+ SHorizontalBox::Slot()
		.Padding(2.f)
		.AutoWidth()
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Padding(2.f)
			[
				SNew(SImage)
				.Image_Lambda([this]()
				{
					return FWeastStyle::Get().GetBrush(GetWeatherDescriptorStyleName(WeastStyle->GetStyleName(), ImageSize));
				})
			]
		];
}

TSharedRef<SWidget> SWeastTitlePanel::BuildHomeLayout() const
{
	return SNew(SVerticalBox)

			//Static textbox: Your Location
			+SVerticalBox::Slot()
			.Padding(0.f, 10.f)
			.AutoHeight()
			[
				SNew(SBox)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SWeastImageWithText)
					.TextColor(WeastStyle->TextColor)
					.Font(WeastStyle->BodyTextStyle.Font)
					.Text(LOCTEXT("YourLocationLabel", "Your Location Now"))
					.ImageOrientation(EWeastView::EWVO_Left)
					.Image(&WeastStyle->LocationIconBrush)
				]
			]

			//FullCityName
			+ SVerticalBox::Slot()
			.Padding(0.f, 0.f, 0.f, 4.f)
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.WrapTextAt(500.f)
					.Font(WeastStyle->TitleTextStyle.Font)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Text_Lambda([this]()
					{
						if(Model.IsValid() && Model->HasFinishedLoading() && Model->GetActiveCity().IsValid())
						{
							return FText::Format(LOCTEXT("FullCityText", "{0}"), FText::FromString(Model->GetActiveCity()->FullCityName));
						}
						return FText::GetEmpty();
					})
				]
			]

			//Image
			+ SVerticalBox::Slot()
			.Padding(0.f, 5.f)
			.AutoHeight()
			[
				SNew(SBox)
				.MaxAspectRatio(1.f)
				.HAlign(HAlign_Center)
				[
					SNew(SImage)
					.Image_Lambda([this]()
						{
							return FWeastStyle::Get().GetBrush(GetWeatherDescriptorStyleName(WeastStyle->GetStyleName(), ImageSize, true));
						})
				]
			]

			//WeatherType
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.AutoHeight()
			.Padding(0.f, 5.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				[
					SNew(SBorder)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Padding(4.f)
					.BorderImage(&WeastStyle->BehindTextIconBrush)
					[
						SNew(STextBlock)
						.Font(WeastStyle->CaptionTextStyle.Font)
						.ColorAndOpacity(WeastStyle->TextColor)
						.Text_Lambda([this]()
						{
								if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetActiveCity().IsValid())
								{
									return FText::Format(LOCTEXT("InfoText", " {0} "), FText::FromString(Model->GetActiveCity()->GetDescription().ToUpper()));
								}
								return FText::GetEmpty();
						})
					]
				]
			]

			//Temperature
			+ SVerticalBox::Slot()
			.Padding(0.f, 4.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Font(WeastStyle->TitleTextStyle.Font)
					.ColorAndOpacity(WeastStyle->TextColor)
					.Text_Lambda([this]()
					{
							if (Model.IsValid() && Model->HasFinishedLoading() && Model->GetActiveCity().IsValid())
							{
								return FText::Format(LOCTEXT("TemperatureText", "{0}{1}"), Model->GetActiveCity()->GetTemperature(), GetTemperatureUnit());
							}
							return FText::GetEmpty();
					})
				]
			];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FText SWeastTitlePanel::GetTemperatureUnit() const
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

FName SWeastTitlePanel::GetWeatherDescriptorStyleName(FString InStyleName, FString InSize, bool bUseActive) const
{
	FName DescriptorStyleName = FName(TEXT(""));
	if (Model.IsValid() && Model->HasFinishedLoading())
	{
		if(bUseActive && Model->GetActiveCity().IsValid())
		{
			DescriptorStyleName = UE::Weast::FWeastCommon::GetWeatherDescriptorStyleName(
				Model->GetActiveCity()->current.weather.id,
				FName(Model->GetActiveCity()->current.weather.icon),
				InStyleName,
				InSize);
		}
		else if (Model->GetCityById(CityGuid).IsValid())
		{
			DescriptorStyleName = UE::Weast::FWeastCommon::GetWeatherDescriptorStyleName(
				Model->GetCityById(CityGuid)->current.weather.id,
				FName(Model->GetCityById(CityGuid)->current.weather.icon),
				InStyleName,
				InSize);
		}
	}
	return DescriptorStyleName;
}

#undef LOCTEXT_NAMESPACE
