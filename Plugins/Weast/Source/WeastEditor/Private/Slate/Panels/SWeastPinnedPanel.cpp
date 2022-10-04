
#include "Slate/Panels/SWeastPinnedPanel.h"

#include "Components/HorizontalBox.h"
#include "Slate/Panels/SWeastMultiViewPanel.h"
#include "Slate/Input/SWeastPinnedButton.h"

#include "SlateOptMacros.h"
#include "Styling/WeastWidgetStyle.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SScrollBox.h"

#define LOCTEXT_NAMESPACE "SWeastPinnedCity"

SWeastPinnedPanel::~SWeastPinnedPanel()
{
	if(Model.IsValid())
	{
		Model->OnFinishedLoading().RemoveAll(this);
	}
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SWeastPinnedPanel::Construct(const FArguments& InArgs, const IWeastModelRef& InModel)
{
	Model = InModel;
	WeastStyle = FWeastWidgetStyle::GetCurrentStyle();
	Grid = SNew(SUniformGridPanel).SlotPadding(FMargin(2.f,2.f));

	if(Model.IsValid())
	{
		Model->OnFinishedLoading().AddSP(this, &SWeastPinnedPanel::PopulateGrid);
	}

	PopulateGrid();

	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.Padding(10.f, 15.f)
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SSearchBox)
					.Style(&WeastStyle->SearchBoxStyle)
					.HintText(LOCTEXT("SearchBox","Search through the city"))
					.OnTextChanged(this, &SWeastPinnedPanel::OnSearchBoxTextChanged)
				]
			]
			+ SVerticalBox::Slot()
			//.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SScrollBox)
					.Orientation(EOrientation::Orient_Vertical)
					.ScrollBarAlwaysVisible(false)
					.ConsumeMouseWheel(EConsumeMouseWheel::WhenScrollingPossible)

					+ SScrollBox::Slot()
					.HAlign(HAlign_Center)
					[
						Grid.ToSharedRef()
					]
				]
			]
		];
}

void SWeastPinnedPanel::OnSearchBoxTextChanged(const FText& InText)
{
	if (InText.IsEmpty())
	{
		PopulateGrid();
		return;
	}
	if(InText.ToString().Len() <= 3)
	{
		return;
	}
	PopulateGrid(InText);
}

bool SWeastPinnedPanel::CityHasTextInAnyParameter(const FText& InSearchText, TSharedPtr<FWeatherCityRoute> InCity) const
{
	return	InCity->City.Contains(InSearchText.ToString()) ||
			InCity->Region.Contains(InSearchText.ToString()) ||
			InCity->Country.Contains(InSearchText.ToString());
}

void SWeastPinnedPanel::PopulateGrid()
{
	if (!Model.IsValid() || !Model->HasFinishedLoading())
	{
		return;
	}
	int32 Column = 0;
	int32 Row = 0;
	Grid->ClearChildren();
	for (const TSharedPtr<FWeatherCityRoute> City : Model->GetAllCity())
	{
		if (City->IsPinned)
		{
			AddCitySlot(Column, Row, City->Id);
			Row += Column % NumberOfColumns;
			Column = (Column + 1) % NumberOfColumns;
		}
	}
}

void SWeastPinnedPanel::PopulateGrid(const FText& InSearchText)
{
	if (!Model.IsValid() || !Model->HasFinishedLoading())
	{
		return;
	}
	int32 Column = 0;
	int32 Row = 0;
	Grid->ClearChildren();
	for (const TSharedPtr<FWeatherCityRoute> City : Model->GetAllCity())
	{
		if (CityHasTextInAnyParameter(InSearchText, City))
		{
			AddCitySlot(Column, Row, City->Id);
			Row += Column % NumberOfColumns;
			Column = (Column + 1) % NumberOfColumns;
		}
	}
}

void SWeastPinnedPanel::AddCitySlot(int32 InColumn, int32 InRow, FGuid InId)
{
	Grid->AddSlot(InColumn, InRow)
		.AttachWidget
		(
			SNew(SBorder)
			.BorderImage(&WeastStyle->PinnedBorderBrush)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
				.Padding(4.f)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					[
						SNew(SWeastMultiViewPanel, FViewArgsFactory::CreatePinnedViewArgs(), Model.ToSharedRef())
						.ImageSize(TEXT("Large"))
						.CityGuid(InId)
						.WidgetIndex(EWeastView::EWVL_Pinned)
					]
					//FavouriteIcon
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Bottom)
					.Padding(0.f, 4.f)
					[
						SNew(SImage)
						.Image(&WeastStyle->FavouriteIconBrush)
						.Visibility(this, &SWeastPinnedPanel::FavouriteVisibility, InId)
					]
					//Pinned Icon
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Bottom)
					.Padding(0.f, 4.f)
					[
						SNew(SImage)
						.Image(&WeastStyle->PinIconBrush)
						.Visibility(this, &SWeastPinnedPanel::PinnedVisibility, InId)
					]

				]
				+ SOverlay::Slot()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(0.5f)
					[
						//Pinning
						SNew(SWeastPinnedButton)
						.ButtonImage(&WeastStyle->PinIconBrush)
						.ButtonStyle(&WeastStyle->ButtonLeftStyle)
						.CityGuid(InId)
						.OnPinnedButtonClicked_Lambda([this](FGuid InGuid)
						{
							if (!Model.IsValid() || !Model->HasFinishedLoading())
							{
								return;
							}
							if (!Model->PinUnpinById(InGuid))
							{
								return;
							}
							PopulateGrid();
						})
					]
					+ SHorizontalBox::Slot()
					.FillWidth(0.5f)
					[
						//SetActive
						SNew(SWeastPinnedButton)
						.ButtonImage(&WeastStyle->FavouriteIconBrush)
						.ButtonStyle(&WeastStyle->ButtonRightStyle)
						.CityGuid(InId)
						.OnPinnedButtonClicked_Lambda([this](FGuid InGuid)
						{
							if(!Model.IsValid() || !Model->HasFinishedLoading())
							{
								return;
							}
							if(Model->GetActiveCity()->Id == InGuid)
							{
								return;
							}
							if (!Model->SetNewActiveCity(InGuid))
							{
								return;
							}
							PopulateGrid();
						})
					]
				]
			]
	);
}

EVisibility SWeastPinnedPanel::PinnedVisibility(FGuid InId) const
{
	if (!Model.IsValid() || !Model->HasFinishedLoading())
	{
		return EVisibility::Collapsed;
	}
	if (!(Model->GetActiveCityId() == InId))
	{
		if (Model->GetCityById(InId).IsValid() && Model->GetCityById(InId)->IsPinned)
		{
			return EVisibility::Visible;
		}
	}
	return EVisibility::Collapsed;
}

EVisibility SWeastPinnedPanel::FavouriteVisibility(FGuid InId) const
{
	if (!Model.IsValid() || !Model->HasFinishedLoading())
	{
		return EVisibility::Collapsed;
	}
	if (Model->GetActiveCityId() == InId)
	{
		return EVisibility::Visible;
	}
	return EVisibility::Collapsed;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE