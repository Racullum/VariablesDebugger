// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


class VARIABLESDEBUGGER_API FVariablesDebuggerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	void OnPostPIEStarted(bool bIsSimulating);
	void OnSettingsChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);
	TSharedRef<SWidget> CreateDebuggerWidgetContent();
	TSharedRef<SDockTab> SpawnDebuggerTab(const FSpawnTabArgs& Args);

private:
	TWeakPtr<SDockTab> DebuggerTab;

	void RegisterMenus();
	TSharedPtr<FUICommandList> PluginCommands;
};
