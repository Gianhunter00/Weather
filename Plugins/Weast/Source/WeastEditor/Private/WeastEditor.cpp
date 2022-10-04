// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeastEditor.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "IWeast.h"
#include "Commands/WeastCommands.h"
#include "LevelEditor.h"

#include "Styling/WeastStyle.h"
#include "ToolMenus.h"

#include "Slate/SWeast.h"
#include "Slate/Private/Framework/Docking/SDockingArea.h"

#include "Styling/WeastWidgetStyle.h"

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

static const FName WeastTabName("Weast");

#define LOCTEXT_NAMESPACE "WeastEditor"

void UE::Weast::Private::FWeastEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	BindDelegates();

	RegisterStyles();

	RegisterCommands();

	RegisterExtensions();

	RegisterTabs();
}

void UE::Weast::Private::FWeastEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (UObjectInitialized())
	{
		UnregisterStyles();

		UnregisterCommands();

		UnregisterTabs();

		UnbindDelegates();
	}
}

void UE::Weast::Private::FWeastEditorModule::BindDelegates()
{
	OnWeastTabClosedDelegate.BindRaw(this, &FWeastEditorModule::OnWeastTabClosed);
}

void UE::Weast::Private::FWeastEditorModule::UnbindDelegates()
{
	if (OnWeastTabClosedDelegate.IsBoundToObject(this))
	{
		OnWeastTabClosedDelegate.Unbind();
	}
}

void UE::Weast::Private::FWeastEditorModule::AddMenuExtensions(class FMenuBuilder& InMenuBuilder)
{
	InMenuBuilder.BeginSection("Weast", LOCTEXT("WeastSection", "Weast"));

	{
		InMenuBuilder.AddMenuEntry(
			FWeastCommands::Get().LaunchWeast,
			NAME_None,
			TAttribute<FText>(),
			TAttribute<FText>(),
			FSlateIcon(FWeastStyle::GetStyleSetName(), "Weast.Launch.Small")
		);
	}

	InMenuBuilder.EndSection();
}

void UE::Weast::Private::FWeastEditorModule::AddToolbarExtensions(class FToolBarBuilder& InToolBarBuilder)
{
	InToolBarBuilder.AddSeparator("Weast");

	InToolBarBuilder.AddToolBarButton(
		FWeastCommands::Get().LaunchWeast,
		NAME_None,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FWeastStyle::GetStyleSetName(), "Weast.Launch.Medium")
	);
}

void UE::Weast::Private::FWeastEditorModule::RegisterCommands()
{
	FWeastCommands::Register();

	WeastCommands = MakeShareable(new FUICommandList);

	WeastCommands->MapAction(
		FWeastCommands::Get().LaunchWeast,
		FExecuteAction::CreateRaw(this, &FWeastEditorModule::OnWeastButtonClicked),
		FCanExecuteAction());
}

void UE::Weast::Private::FWeastEditorModule::RegisterExtensions()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

		MenuExtender->AddMenuExtension("LevelEditor",
			EExtensionHook::Before,
			WeastCommands,
			FMenuExtensionDelegate::CreateRaw(this, &FWeastEditorModule::AddMenuExtensions));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

		ToolbarExtender->AddToolBarExtension("Content",
			EExtensionHook::After,
			WeastCommands,
			FToolBarExtensionDelegate::CreateRaw(this, &FWeastEditorModule::AddToolbarExtensions));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void UE::Weast::Private::FWeastEditorModule::RegisterStyles()
{
	FWeastStyle::Initialize();

	FWeastStyle::ReloadTextures();
}

void UE::Weast::Private::FWeastEditorModule::RegisterTabs()
{
#if WITH_EDITOR

	FGlobalTabmanager::Get()->RegisterTabSpawner(WeastTabName, FOnSpawnTab::CreateRaw(this, &FWeastEditorModule::OnSpawnWeastTab));

#else

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(WeastTabName, FOnSpawnTab::CreateRaw(this, &FWeastEditorModule::OnSpawnWeastTab))
		.SetDisplayName(LOCTEXT("WeastTabTitle", "Weast"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

#endif // WITH_EDITOR
}

void UE::Weast::Private::FWeastEditorModule::UnregisterCommands()
{
	if (WeastCommands.IsValid())
	{
		WeastCommands->UnmapAction(FWeastCommands::Get().LaunchWeast);
	}

	FWeastCommands::Unregister();
}

void UE::Weast::Private::FWeastEditorModule::UnregisterStyles()
{
	FWeastStyle::Shutdown();
}

void UE::Weast::Private::FWeastEditorModule::UnregisterTabs()
{
#if WITH_EDITOR

	FGlobalTabmanager::Get()->UnregisterTabSpawner(WeastTabName);

#else

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WeastTabName);

#endif // WITH_EDITOR
}

TSharedRef<SDockTab> UE::Weast::Private::FWeastEditorModule::OnSpawnWeastTab(const FSpawnTabArgs& SpawnTabArgs)
{
	const TSharedRef<SDockTab> WeastTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab);

	WeastTab->SetTabIcon(FWeastStyle::Get().GetBrush(TEXT("Weast.Launch.Small")));

	IWeastModule& WeastModule = FModuleManager::LoadModuleChecked<IWeastModule>("Weast");

	check(&WeastModule);

	IWeastModelRef Model = WeastModule.GetWeastModel();

	Model->BeginSession();

	WeastTab->SetContent(SNew(SWeast, WeastTab, SpawnTabArgs.GetOwnerWindow(), Model));

	WeastTab->SetOnTabClosed(OnWeastTabClosedDelegate);

	return WeastTab;
}

void UE::Weast::Private::FWeastEditorModule::OnWeastButtonClicked()
{
	if (TSharedPtr<SDockTab> WeastTab = FGlobalTabmanager::Get()->TryInvokeTab(WeastTabName))
	{
		if (TSharedPtr<SWindow> ParentWindow = WeastTab->GetParentWindow())
		{
			FWindowSizeLimits SizeLimits = ParentWindow->GetSizeLimits();

			SizeLimits.SetMinHeight(720.f);

			SizeLimits.SetMinWidth(540.f);

			ParentWindow->SetSizeLimits(SizeLimits);
		}
	}
}

void UE::Weast::Private::FWeastEditorModule::OnWeastTabClosed(TSharedRef<SDockTab> InClosingTab)
{
	IWeastModule& WeastModule = FModuleManager::LoadModuleChecked<IWeastModule>("Weast");

	check(&WeastModule);

	IWeastModelRef Model = WeastModule.GetWeastModel();

	Model->EndSession();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(UE::Weast::Private::FWeastEditorModule, WeastEditor)
