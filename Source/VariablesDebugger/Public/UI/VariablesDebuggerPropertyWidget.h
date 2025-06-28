// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VariablesDebuggerPropertyWidget.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWidgetValueChanged, FName, PropertyName, const FString&, NewValueAsString);

UCLASS(Abstract, Blueprintable)
class VARIABLESDEBUGGER_API UVariablesDebuggerPropertyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// Creates 
	UPROPERTY()
	FOnWidgetValueChanged OnValueChanged;

	UFUNCTION(BlueprintImplementableEvent, Category = "VariablesDebugger")
	void InitializedFromProperty();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "VariablesDebugger")
	FString GetValueAsString();
	
	UFUNCTION(BlueprintCallable, Category = "VariablesDebugger")
	void SetPropertyValueByName(AActor* Actor, const FString& NewValueAsString);

	UFUNCTION(BlueprintCallable, Category = "VariablesDebugger")
	void OnWidgetValueChanged(const FString& NewValueAsString);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "VariablesDebugger")
	FString GetPropertyName();
	
	virtual void EmitValueChanged_Implementation()
	PURE_VIRTUAL(UVariablesDebuggerPropertyWidget::EmitValueChanged_Implementation, );
	FProperty* Property;
	
	void* PropertyContainer;

	void InitializeFromProperty(FProperty* NewProperty, void* ValueContainer);
private:
	FString ValueAsString = "";

};
