// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/UnrealType.h"
#include "Blueprint/UserWidget.h"
#include "AllowedClassAndWidgetMap.h"
#include "VariablesDebuggerSettings.generated.h"

/**
 * 
 */
UCLASS(config=Editor, defaultconfig, meta = (DisplayName = "Variables Debugger Settings"))
class VARIABLESDEBUGGER_API UVariablesDebuggerSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	// Allow user to select a list of classes
	// Combined class + property-widget map
	UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Variables Debugger|Settings")
	TArray<FAllowedClassAndWidgetMap> AllowedClassMappings;

	// Allow user to select a UUserWidget that will populate the tabbed window
	UPROPERTY(EditAnywhere, config, Category="Variables Debugger|Settings", BlueprintReadWrite, meta = (MetaClass = "Object", AllowAbstract = false))
	TSoftClassPtr<UUserWidget> UserSpecifiedWidget;

	UFUNCTION(BlueprintPure, Category = "Variables Debugger")
	static UVariablesDebuggerSettings* Get() { return GetMutableDefault<UVariablesDebuggerSettings>(); }

	static TArray<FProperty*> GetEligiblePropertyTypes(UClass* Class);

	TMap<FName, TSubclassOf<UVariablesDebuggerPropertyWidget>> PropertyToWidgetMap;

	#if WITH_EDITOR
		virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

private:
	TSet<UClass*> AllowedClasses;
};
