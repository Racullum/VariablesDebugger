#include "UI/VariablesDebuggerPropertyWidget.h"

FString UVariablesDebuggerPropertyWidget::GetValueAsString()
{
	return ValueAsString;
}

void UVariablesDebuggerPropertyWidget::SetPropertyValueByName(AActor* Actor, const FString& NewValueAsString)
{
	UObject* OwnerObject = Actor;
	void* ValuePtr = Property->ContainerPtrToValuePtr<void>(PropertyContainer);
	if (Property->ImportText_Direct(*NewValueAsString, ValuePtr, OwnerObject, PPF_None, nullptr))
	{
		ValueAsString = NewValueAsString;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to import value '%s' into property '%s'"),
			*NewValueAsString, *Property->GetName());
	}

}

void UVariablesDebuggerPropertyWidget::OnWidgetValueChanged(const FString& NewValueAsString)
{
	ValueAsString = NewValueAsString;

	// Tell anyone listening (e.g. your Variables-Debugger window) which
	// reflected property changed and what the user typed.
	OnValueChanged.Broadcast(Property ? Property->GetFName() : NAME_None,
							 NewValueAsString);
}

void UVariablesDebuggerPropertyWidget::InitializeFromProperty(FProperty* NewProperty, void* ValueContainer)
{
	FString ValueString;
	NewProperty->ExportTextItem_InContainer(ValueString, ValueContainer, nullptr, nullptr, 0);

	this->Property = NewProperty;
	this->PropertyContainer = ValueContainer;
	this->ValueAsString = ValueString;

	InitializedFromProperty();
	
}

FString UVariablesDebuggerPropertyWidget::GetPropertyName()
{
	return Property ? Property->GetFName().ToString() : "";
}
