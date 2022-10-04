// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IWeastEditor.h"

class FToolBarBuilder;
class FMenuBuilder;

namespace UE::Weast::Private
{
	class FWeastEditorModule  final : public IWeastEditorModule
	{
	public:

		//~ BEGIN : IModuleInterface Implementation

		virtual void StartupModule() override;
		
		virtual void ShutdownModule() override;
		
		//~ END : IModuleInterface Implementation

		/**
		 * Implementation(s)
		 */

	private:
		
		/**
		 * Editor Widget Extension(s)
		 */
		void BindDelegates();

		void UnbindDelegates();
		/**
		 * Adds Weast UI Extensions to Menubar.
		 * 
		 * @param InMenuBuilder
		 */
		void AddMenuExtensions(class FMenuBuilder& InMenuBuilder);

		/**
		 * Adds Weast UI Extensions to Toolbar.
		 *
		 * @param InToolBarBuilder
		 */
		void AddToolbarExtensions(class FToolBarBuilder& InToolBarBuilder);

		/**
		 * Registration(s)
		 */

		/**
		 * Registers Weast's Slate UI Commands to the Editor's Commands List.
		 */
		void RegisterCommands();

		/**
		 * Registers Weast's Slate UI Commands to the Editor's Slate UI.
		 */
		void RegisterExtensions();

		/**
		 * Registers Weast's Slate Style Set to the Editor's Style Set.
		 */
		void RegisterStyles();

		/**
		 * Registers Weast's Tabs to the Editor's Global Tab Manager.
		 */
		void RegisterTabs();

		/**
		 * Unregistration(s)
		 */

		/**
		 * Unregisters Weast's Slate UI Commands from the Editor's Commands List.
		 */
		void UnregisterCommands();

		/**
		 * Unregisters Weast's Slate Style Set from the Editor's Style Set.
		 */
		void UnregisterStyles();

		/**
		 * Unregisters Weast's Tabs from the Editor's Global Tab Manager.
		 */
		void UnregisterTabs();

		/**
		 * Delegate(s)
		 */

		/**
		 * Creates a new Weast tab.
		 * 
		 * @param InSpawnTabArgs The arguments for the tab to be spawned.
		 * 
		 * @return The spawned tab.
		 */
		TSharedRef<class SDockTab> OnSpawnWeastTab(const class FSpawnTabArgs& SpawnTabArgs);

		/**
		 * This function will be bound to Command (by default it will bring up Weast window).
		 */
		void OnWeastButtonClicked();

		void OnWeastTabClosed(TSharedRef<class SDockTab> InClosingTab);

		/**
		 * Attribute(s)
		 */

	private:

		/** Holds the UI Command(s) with mapped action(s). */
		TSharedPtr<class FUICommandList> WeastCommands;

		SDockTab::FOnTabClosedCallback OnWeastTabClosedDelegate;
	};
}