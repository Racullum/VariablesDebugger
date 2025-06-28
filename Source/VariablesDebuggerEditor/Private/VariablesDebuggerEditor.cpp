#include "VariablesDebuggerEditor.h"

#include "FPropertyDropdownToWidgetCustomization.h"

#define LOCTEXT_NAMESPACE "FVariablesDebuggerEditorModule"

void FVariablesDebuggerEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyEditor.RegisterCustomPropertyTypeLayout(
		"PropertyDropdownToWidget", // Must match the struct name exactly
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FPropertyDropdownToWidgetCustomization::MakeInstance)
	);

	PropertyEditor.NotifyCustomizationModuleChanged();
}

void FVariablesDebuggerEditorModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FVariablesDebuggerEditorModule, VariablesDebuggerEditor)