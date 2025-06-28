// Fill out your copyright notice in the Description page of Project Settings.

#include "FPropertyDropdownToWidgetCustomization.h"
#include "IDetailChildrenBuilder.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "SSearchableComboBox.h"
#include "Settings/VariablesDebuggerSettings.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SComboBox.h"



TSharedRef<IPropertyTypeCustomization> FPropertyDropdownToWidgetCustomization::MakeInstance()
 {
	return MakeShareable(new FPropertyDropdownToWidgetCustomization);
}

void FPropertyDropdownToWidgetCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils&)
{
	// Optional: add header UI
	TSharedPtr<IPropertyHandle> DropdownHandle = StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FPropertyDropdownToWidget, PropertyDropdown));

	HeaderRow
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString(""))
	]
	.ValueContent()
	.MinDesiredWidth(250.f)
	[
		SNew(STextBlock)
		.Text_Lambda([DropdownHandle]() -> FText {
			FName Value;
			if (DropdownHandle->GetValue(Value) == FPropertyAccess::Success)
			{
				return FText::FromName(Value);
			}
			return FText::FromString("Unset");
		})
	];
}

void FPropertyDropdownToWidgetCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils&)
{
	auto PropertyDropdownHandle = StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FPropertyDropdownToWidget, PropertyDropdown));
	auto WidgetHandle = StructHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FPropertyDropdownToWidget, Widget));
	TArray<void*> RawData;
	StructHandle->AccessRawData(RawData);
	UVariablesDebuggerSettings* Settings;
	if (RawData.Num() > 0)
	{
		Settings = reinterpret_cast<UVariablesDebuggerSettings*>(RawData[0]);
	}
	UClass* SourceClass = GetOwningClassFromParent(StructHandle);

	if (SourceClass)
	{
		for (TFieldIterator<FProperty> It(SourceClass, EFieldIteratorFlags::IncludeSuper); It; ++It)
		{
			UE_LOG(LogTemp, Warning, TEXT("Property: %s"), *It->GetName());
			PropertyNames.Add(MakeShared<FString>(It->GetFName().ToString()));
		}
	}

	ChildBuilder.AddCustomRow(FText::FromString("Property"))
	.NameContent()
	[
		PropertyDropdownHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(300)
	[
		SNew(SSearchableComboBox)
		.OptionsSource(&PropertyNames)
		.OnGenerateWidget_Lambda([](TSharedPtr<FString> InItem) {
			return SNew(STextBlock).Text(FText::FromString(*InItem));
		})
		.OnSelectionChanged_Lambda([PropertyDropdownHandle, WidgetHandle, Settings](TSharedPtr<FString> NewItem, ESelectInfo::Type) {
			if (NewItem.IsValid())
			{
				// Populate Settings object with a new entry in the PropertyToWidgetMap
				UObject* WidgetObjectFromStruct;
				WidgetHandle->GetValue(WidgetObjectFromStruct);
				UVariablesDebuggerPropertyWidget* CurrentWidget = Cast<UVariablesDebuggerPropertyWidget>(WidgetObjectFromStruct);
				if (CurrentWidget && Settings)
				{
					Settings->PropertyToWidgetMap.Add(FName(**NewItem), CurrentWidget->GetClass());
				}

				// Set the actual property value in the parent struct
				PropertyDropdownHandle->SetValue(*NewItem);
			}
		})
		[
			SNew(STextBlock).Text_Lambda([PropertyDropdownHandle]() {
				FName Current;
				PropertyDropdownHandle->GetValue(Current);
				return FText::FromName(Current);
			})
		]
	];

	// Default rendering for the widget class
	ChildBuilder.AddProperty(WidgetHandle.ToSharedRef());

	// I think here we add property/widget to a map.
	
}

UClass* FPropertyDropdownToWidgetCustomization::GetOwningClassFromParent(TSharedRef<IPropertyHandle> StructHandle) const
{
	// This is the AllowedClassAndWidgetMap struct
	TSharedPtr<IPropertyHandle> ParentHandle = StructHandle->GetParentHandle();

	while (ParentHandle.IsValid())
	{
		// Check if this parent is of type FClassToPropertyMap
		if (ParentHandle->GetProperty() &&
			ParentHandle->GetProperty()->GetCPPType(nullptr, 0).Contains("FAllowedClassAndWidgetMap"))
		{
			TArray<void*> RawData;
			ParentHandle->AccessRawData(RawData);
			if (RawData.Num() > 0)
			{
				FAllowedClassAndWidgetMap* ParentStruct = reinterpret_cast<FAllowedClassAndWidgetMap*>(RawData[0]);
				if (ParentStruct && ParentStruct->Class)
				{
					return ParentStruct->Class.Get();
				}
			}
		}

		ParentHandle = ParentHandle->GetParentHandle(); // climb upward
	}

	return nullptr;
}


// Add default functionality here for any IFPropertyDropdownToWidgetCustomization functions that are not pure virtual.
