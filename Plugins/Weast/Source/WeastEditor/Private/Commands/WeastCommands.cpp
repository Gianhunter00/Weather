// Copyright Epic Games, Inc. All Rights Reserved.

#include "Commands/WeastCommands.h"

#define LOCTEXT_NAMESPACE "FWeastModule"

FWeastCommands::FWeastCommands()
	: TCommands<FWeastCommands>(TEXT("Weast"), NSLOCTEXT("Contexts", "Weast", "Weast Plugin"), NAME_None, FWeastStyle::GetStyleSetName())
{
}

void FWeastCommands::RegisterCommands()
{
	UI_COMMAND(LaunchWeast, "Weast", "Bring up Weast window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
