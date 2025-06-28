#pragma once
#include "CoreMinimal.h"
#include "VariablesDebugInfo.generated.h"
USTRUCT(BlueprintType)
struct FVariableDebugInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, Category = "VariablesDebugger")
	FName Name;
	
	UPROPERTY(BlueprintReadOnly, Category = "VariablesDebugger")
	FString Type;
	
	UPROPERTY(BlueprintReadOnly, Category = "VariablesDebugger")
	FString ValueAsString;
};
