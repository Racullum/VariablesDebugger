// Copyright Epic Games, Inc. All Rights Reserved.
#include "VariablesDebuggerModule.h"

#include "Blueprint/UserWidget.h"   // <-- pulls in both the class AND the template
#include "VariablesDebuggerCommands.h"
#include "Settings/VariablesDebuggerSettings.h"
#include "Misc/MessageDialog.h"
#include "UMG.h"


#define LOCTEXT_NAMESPACE "FVariablesDebuggerModule"


void FVariablesDebuggerModule::StartupModule()
{
	FVariablesDebuggerCommands::Register();
	

	// Create command list and bind actions
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FVariablesDebuggerCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FVariablesDebuggerModule::PluginButtonClicked),
		FCanExecuteAction());
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FVariablesDebuggerModule::RegisterMenus));
	FEditorDelegates::PostPIEStarted.AddRaw(this, &FVariablesDebuggerModule::OnPostPIEStarted);

	if (UVariablesDebuggerSettings* Settings = GetMutableDefault<UVariablesDebuggerSettings>())
	{
        Settings->OnSettingChanged().AddRaw(this, &FVariablesDebuggerModule::OnSettingsChanged);
	}
	
}


void FVariablesDebuggerModule::ShutdownModule()
{

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FVariablesDebuggerStyle::Shutdown();

	FVariablesDebuggerCommands::Unregister();
	
}

void FVariablesDebuggerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools.Debug");
	if (ToolbarMenu)
	{
		FToolMenuSection& Section = ToolbarMenu->AddSection("Variables Debugger", LOCTEXT("VariablesDebuggerLabel", "Variables Debugger"));
		Section.AddMenuEntry(
			"VariablesDebuggerMenuEntry",
			LOCTEXT("VariablesDebuggerMenuEntryLabel", "Open Variables Debugger"),
			LOCTEXT("VariablesDebuggerEntryTooltip", "Allows you to edit every variable of a specified class."),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this, &FVariablesDebuggerModule::PluginButtonClicked))
		);
	}
	else
	{
		// Handle the error, e.g., log a message
		UE_LOG(LogTemp, Warning, TEXT("Menu not found: /Game/Plugins/VariablesDebugger/Content/EUW_ToolMenuEntry_VariableDebugger"));
	}
	{
		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
		{
			FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FVariablesDebuggerCommands::Get().PluginAction));
			Entry.SetCommandList(PluginCommands);
		}
	}
}

void FVariablesDebuggerModule::OnPostPIEStarted(bool bIsSimulating)
{
	if (DebuggerTab.IsValid())
	{
		if (TSharedPtr<SDockTab> Tab = DebuggerTab.Pin())
		{
			// Optional: Clear and re-insert new content
			Tab->SetContent(CreateDebuggerWidgetContent());
		}
	}

}

void FVariablesDebuggerModule::OnSettingsChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (UVariablesDebuggerSettings* ChangedSettings = Cast<UVariablesDebuggerSettings>(Object))
	{
		UE_LOG(LogTemp, Warning, TEXT("Settings changed: %s"), *PropertyChangedEvent.GetPropertyName().ToString());

	}
}


void FVariablesDebuggerModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner("VariablesDebuggerTab",
	FOnSpawnTab::CreateRaw(this, &FVariablesDebuggerModule::SpawnDebuggerTab))
	.SetDisplayName(FText::FromString("Variables Debugger"))
	.SetMenuType(ETabSpawnerMenuType::Hidden);
	FTabId TabId("VariablesDebuggerTab");
	DebuggerTab = FGlobalTabmanager::Get()->TryInvokeTab(TabId);
}

TSharedRef<SDockTab> FVariablesDebuggerModule::SpawnDebuggerTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> Tab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			CreateDebuggerWidgetContent()
		];
	DebuggerTab = Tab;
	return Tab;
}

// Helper function
UWorld* GetPieWorld()
{
	for (const FWorldContext& Context : GEngine->GetWorldContexts())
	{
		if (Context.WorldType == EWorldType::PIE)
		{
			return Context.World();
		}
	}
	return nullptr;
}


TSharedRef<SWidget> FVariablesDebuggerModule::CreateDebuggerWidgetContent()
{
	
	// 1) load your UUserWidget subclass
	UClass* RawClass = GetDefault<UVariablesDebuggerSettings>()
						  ->UserSpecifiedWidget
						  .LoadSynchronous();
	if (!RawClass)
	{
		return SNew(STextBlock).Text(FText::FromString("No widget class"));
	}

	// 2) cast into TSubclassOf<UUserWidget>
	TSubclassOf<UUserWidget> WidgetClass = RawClass;

	// 3) check engine & viewport
	if (!GEngine || !GEngine->GameViewport)
	{
		return SNew(STextBlock).Text(FText::FromString("No Active World Detected"));
	}

	// 4) get your PIE world
	UWorld* World = GetPieWorld();
	if (!World)
	{
		return SNew(STextBlock).Text(FText::FromString("No world found"));
	}

	// This does
	//UUserWidget* WidgetInstance = UUserWidget::CreateWidgetInstance(*World, WidgetClass, "Name");
	//This doesn't work
	UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(World, WidgetClass);

    if (!WidgetInstance)
	{
		return SNew(STextBlock).Text(FText::FromString("Widget creation failed"));
	}

	// 6) take the Slate widget from your UserWidget
	return WidgetInstance->TakeWidget();
}





#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVariablesDebuggerModule, VariablesDebugger)