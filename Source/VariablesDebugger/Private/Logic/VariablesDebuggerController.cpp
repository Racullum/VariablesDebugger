#include "Logic/VariablesDebuggerController.h"

#include "Settings/VariablesDebuggerSettings.h"

TWeakObjectPtr<UVariablesDebuggerController> UVariablesDebuggerController::Singleton;


UVariablesDebuggerController* UVariablesDebuggerController::GetController(UObject* WorldContextObject)
{
	if (Singleton.IsValid())
	{
		return Singleton.Get();
	}

	UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	UVariablesDebuggerController* NewInstance = NewObject<UVariablesDebuggerController>(World);
	Singleton = NewInstance;
	return NewInstance;
}

void UVariablesDebuggerController::SetSelectedClass(TSubclassOf<AActor> NewClass)
{
	if (NewClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NewClass is null."));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Setting selected class to %s"), *NewClass->GetName().Replace(TEXT("."), TEXT("")));
	SelectedClass = NewClass;
}

TArray<UVariablesDebuggerPropertyWidget*> UVariablesDebuggerController::CreatePropertyWidgetsForActor(
	AActor* TargetActor, UUserWidget* OwningWidget)
{
	TArray<UVariablesDebuggerPropertyWidget*> Result;
	if (!IsValid(TargetActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetActor is null."));
		return Result;
	}

	UClass* TargetClass = TargetActor->GetClass();
	UVariablesDebuggerSettings* Settings = UVariablesDebuggerSettings::Get();
	UWorld* World = OwningWidget->GetWorld();

	// Find the widget mappings for this class
	if (FAllowedClassAndWidgetMap* Found = Algo::FindBy(Settings->AllowedClassMappings, TargetClass,
														&FAllowedClassAndWidgetMap::Class))
	{
		for (const FPropertyDropdownToWidget& Mapping : Found->PropertyToWidgetMap)
		{
			FProperty* Property = TargetClass->FindPropertyByName(Mapping.PropertyDropdown);
			if (!Property)
			{
				UE_LOG(LogTemp, Warning, TEXT("Property %s not found on class %s"), *Mapping.PropertyDropdown.ToString(), *TargetClass->GetName());
				continue;
			}

			UVariablesDebuggerPropertyWidget* Widget = CreateWidget<UVariablesDebuggerPropertyWidget>(
				World,
				Mapping.Widget
			);

			if (!Widget)
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to create widget for %s"), *Mapping.PropertyDropdown.ToString());
				continue;
			}

			Widget->InitializeFromProperty(Property, TargetActor);
			Widget->OnValueChanged.AddDynamic(this, &UVariablesDebuggerController::OnPropertyWidgetValueChange);
			Result.Add(Widget);

			UE_LOG(LogTemp, Warning, TEXT("Created property widget for %s"), *Mapping.PropertyDropdown.ToString());
		}
	}
	
	return Result;
}


void UVariablesDebuggerController::OnPropertyWidgetValueChange(FName PropertyName, const FString& NewValueAsString)
{
	if (SelectedActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Actors array is empty. Please select some actors to apply the change to."));
		return;
	}
	UClass* Class = SelectedClass;
	FProperty* Property = Class->FindPropertyByName(PropertyName);
	if (Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Property %s not found on %s"), *PropertyName.ToString(), *Class->GetName());
		return;
	}
	for (AActor* SelectedActor : SelectedActors)
	{
		void* Container = SelectedActor;
		void* ValuePtr = Property->ContainerPtrToValuePtr<void>(Container);
		if (ValuePtr == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Property->ContainerPtrToValuePtr<void>(%s), returned a null ptr"), *SelectedActor->GetName());
			continue;
		}
		Property->ImportText_Direct(*NewValueAsString, ValuePtr, SelectedActor, PPF_None);
		#if WITH_EDITOR
				SelectedActor->PostEditChange();
				SelectedActor->MarkPackageDirty();
		#endif
	}

}
