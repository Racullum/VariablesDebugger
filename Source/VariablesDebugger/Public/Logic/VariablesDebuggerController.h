// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/VariablesDebuggerPropertyWidget.h"
#include "UObject/Object.h"
#include "VariablesDebuggerController.generated.h"

/** Controller class responsible for handling and managing the debugging of variables in the application */
UCLASS(BlueprintType)
class VARIABLESDEBUGGER_API UVariablesDebuggerController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="VariablesDebugger", meta=(WorldContext="WorldContextObject"))
	static UVariablesDebuggerController* GetController(UObject* WorldContextObject);
	// SelectedClass - GETTERS/SETTERS
	UFUNCTION(BlueprintCallable, Category = "Variables Debugger")
	void SetSelectedClass(TSubclassOf<AActor> NewClass);
	UFUNCTION(BlueprintCallable, Category = "Variables Debugger")
	TSubclassOf<AActor> GetSelectedClass() { return SelectedClass; }
	
	// SelectedActor - GETTERS/SETTERS 
	UFUNCTION(BlueprintCallable, Category = "Variables Debugger")
	void SetSelectedActors(const TArray<AActor*>& Actors) { SelectedActors = Actors;}
	UFUNCTION(BlueprintCallable, Category = "Variables Debugger")
	TArray<AActor*> GetSelectedActors() { return SelectedActors; }
	UFUNCTION()
	void OnPropertyWidgetValueChange(FName PropertyName, const FString& NewValueAsString);

	// CreatePropertyWidgetsForActor - Generates an array of the property widgets that are mapped to a class in our Plugin's settings object.
	UFUNCTION(BlueprintCallable, Category = "Variables Debugger")
	TArray<UVariablesDebuggerPropertyWidget*> CreatePropertyWidgetsForActor(AActor* TargetActor, UUserWidget* OwningWidget);


private:
	UPROPERTY()
	TSubclassOf<AActor> SelectedClass;

	UPROPERTY()
	TArray<AActor*> SelectedActors;

	static TWeakObjectPtr<UVariablesDebuggerController> Singleton;

};
