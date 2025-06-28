#pragma once

#include "CoreMinimal.h"
#include "Settings/PropertyDropdownToWidget.h"
#include "AllowedClassAndWidgetMap.generated.h"

USTRUCT(BlueprintType)
struct FAllowedClassAndWidgetMap
{
	GENERATED_BODY()

	// The user-specified class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Variables Debugger")
	TSubclassOf<AActor> Class;

	// Map of property name to user widget
	UPROPERTY(EditAnywhere, config, Category = "Variables Debugger")
	TArray<FPropertyDropdownToWidget> PropertyToWidgetMap;
};