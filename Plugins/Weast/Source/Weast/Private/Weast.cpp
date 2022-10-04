// Copyright Epic Games, Inc. All Rights Reserved.

#include "Weast.h"

#include "Common/WeastCommon.h"
#include "MessageLogModule.h"
#include "Models/WeastModel.h"

FOnWeastModelInitialized UE::Weast::IWeastModule::WeastModelInitializedDelegate;

IWeastModelPtr UE::Weast::Private::FWeastModule::WeastModelSingleton = NULL;

#define LOCTEXT_NAMESPACE "Weast"

//https://api.openweathermap.org/data/3.0/onecall?lat=33.44&lon=-94.04&exclude=minutely,alerts&appid=b6c959bbca4f0011acdf79b593d454aa


void UE::Weast::Private::FWeastModule::StartupModule()
{
	UE_LOG(LogInit, Log, TEXT("Weast : Starting up..."));
}

void UE::Weast::Private::FWeastModule::ShutdownModule()
{
	UE_LOG(LogExit, Log, TEXT("Weast : Shutting down..."));
	if (WeastModelSingleton.IsValid())
	{
		WeastModelSingleton.Reset();
	}
}

IWeastModelRef UE::Weast::Private::FWeastModule::GetWeastModel()
{
	if (!WeastModelSingleton.IsValid())
	{
		const TSharedPtr<FWeastModel> WeastModel = MakeShareable(new FWeastModel());

		WeastModelSingleton = WeastModel;
		WeastModelInitializedDelegate.Broadcast(*WeastModel);
	}

	return WeastModelSingleton.ToSharedRef();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(UE::Weast::Private::FWeastModule, Weast)
