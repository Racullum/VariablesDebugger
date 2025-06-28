#pragma once
#include "CoreMinimal.h"
#include "UI/VariablesDebuggerPropertyWidget.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyDropdownToWidget.generated.h"

USTRUCT()
struct FPropertyDropdownToWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Variables Debugger", meta = (DisplayName = "Property"))
	FName PropertyDropdown;
	
	UPROPERTY(EditAnywhere, Category="Variables Debugger")
	TSubclassOf<UVariablesDebuggerPropertyWidget> Widget;
	
};


