// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Models/IWeastModel.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeastModelInitialized, IWeastModel& /* Newly Initialized MineSweeper Model */);


namespace UE::Weast
{
    class IWeastModule : public IModuleInterface
    {
	public:

		/**
		 * Singleton-like access to this module's interface.  This is just for convenience!
		 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
		 *
		 * @return Returns singleton instance, loading the module on demand if needed
		 */
		static inline IWeastModule& Get()
		{
			static const FName ModuleName = "Weast";

			return FModuleManager::LoadModuleChecked<IWeastModule>(ModuleName);
		}

		/**
		 * Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true.
		 *
		 * @return True if the module is loaded and ready to use
		 */
		static inline bool IsAvailable()
		{
			static const FName ModuleName = "Weast";

			return FModuleManager::Get().IsModuleLoaded(ModuleName);
		}

		/// <summary>
		/// Gets the Weast model instance.
		/// </summary>
		/// <returns>The MineSweeper Model.</returns>
		virtual IWeastModelRef GetWeastModel() = 0;


	public:

		///
		/// Delegate(s)
		/// 

		/// <summary>
		/// Delegate that is invoked when a Weast model is initialized.
		/// </summary>
    	WEAST_API static FOnWeastModelInitialized WeastModelInitializedDelegate;
    };
}