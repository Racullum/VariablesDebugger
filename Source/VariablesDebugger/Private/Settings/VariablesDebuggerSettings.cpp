#include "Settings/VariablesDebuggerSettings.h"
#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/UnrealTypePrivate.h"


TArray<FProperty*> UVariablesDebuggerSettings::GetEligiblePropertyTypes(UClass* Class)
{
	TArray<FProperty*> Properties;
	for (TFieldIterator<FProperty> It(Class->StaticClass(), EFieldIteratorFlags::IncludeSuper); It; ++It)
	{
		Properties.Add(*It);
	}
	return Properties;
}

#if WITH_EDITOR
void UVariablesDebuggerSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(UVariablesDebuggerSettings, AllowedClassMappings))
	{
		// Log all classes in the array
		for (const FAllowedClassAndWidgetMap& Mapping : AllowedClassMappings)
		{
			if (Mapping.Class)
			{
				UE_LOG(LogTemp, Warning, TEXT("Class: %s"), *Mapping.Class->GetName());
				AllowedClasses.Add(*Mapping.Class);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Class: null"));
			}
		}
	}

	OnSettingChanged().Broadcast(this, PropertyChangedEvent);
}
#endif