// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Styling/WeastStyle.h"

/**
 * Custom set of UI Commands for Weast Plugin.
 */
class FWeastCommands : public TCommands<FWeastCommands>
{
public:

	FWeastCommands();

	//~ BEGIN : TCommands<> Interface

	virtual void RegisterCommands() override;

	//~ END : TCommands<> Interface

	/**
	 * Attribute(s)
	 */

public:

	TSharedPtr<FUICommandInfo> LaunchWeast;
};