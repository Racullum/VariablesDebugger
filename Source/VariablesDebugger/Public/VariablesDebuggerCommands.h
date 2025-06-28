// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "VariablesDebuggerStyle.h"

class FVariablesDebuggerCommands : public TCommands<FVariablesDebuggerCommands>
{
public:

	FVariablesDebuggerCommands()
		: TCommands<FVariablesDebuggerCommands>(TEXT("VariablesDebugger"), NSLOCTEXT("Contexts", "VariablesDebugger", "VariablesDebugger Plugin"), NAME_None, FVariablesDebuggerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
