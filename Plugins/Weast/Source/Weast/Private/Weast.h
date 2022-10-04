// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "IWeast.h"

namespace UE::Weast::Private
{
    class FWeastModule final : public IWeastModule
    {
        //~ BEGIN : IModuleInterface Interface

    public:

        void StartupModule() override;
        
        void ShutdownModule() override;

        //~ END : IModuleInterface Interface

        virtual IWeastModelRef GetWeastModel() override;

    private:

        /// <summary>
        /// The Weast data model singleton.
        /// </summary>
        WEAST_API static IWeastModelPtr WeastModelSingleton;
    };
}
