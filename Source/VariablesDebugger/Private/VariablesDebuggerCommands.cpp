// Copyright Epic Games, Inc. All Rights Reserved.

#include "VariablesDebuggerCommands.h"

#define LOCTEXT_NAMESPACE "FVariablesDebuggerModule"

void FVariablesDebuggerCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Variables Debugger", "Execute VariablesDebugger action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
