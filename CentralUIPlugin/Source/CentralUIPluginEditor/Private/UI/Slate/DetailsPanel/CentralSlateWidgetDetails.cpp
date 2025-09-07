/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#include "CentralSlateWidgetDetails.h"
#include "DetailLayoutBuilder.h"
#include "LogCentralUIPluginEditor.h"
#include "CentralBorder.h"
#include "PropertyHandle.h"
#include "CentralSlateWidgetInterface.h"


TSharedRef<IDetailCustomization> FCentralSlateWidgetDetails::MakeInstance() {
    return MakeShareable(new FCentralSlateWidgetDetails);
}

void FCentralSlateWidgetDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) {
	TArray<TWeakObjectPtr<UObject>> OutObjects;
	DetailBuilder.GetObjectsBeingCustomized(OutObjects);
	if (OutObjects.Num() == 0) {
		// No objects are being customized.
		return;
	}

	/* Helper to find and hide a property recursively, looking into base class up to (including) UWidget. */
	auto HidePropertiesRecursive = [&DetailBuilder](auto&& HidePropertiesRecursive, const FString& InPropertyName, const UClass* InContainerClass) {
		if (!IsValid(InContainerClass) || !InContainerClass->IsChildOf(UWidget::StaticClass())) {
			// If not valid, or not a UWidget, it is irrelevant.
			UE_LOG(LogCentralUIPluginEditor, Warning, TEXT("InContainerClass is invalid for property: %s. Skipping."), *InPropertyName);
			return;		
		}

		const TSharedRef<IPropertyHandle> PropHandleX = DetailBuilder.GetProperty(FName(InPropertyName), InContainerClass);
		if (!PropHandleX->GetProperty()) {
			// Attempt to find the property on the parent. Seems it must be the exact class it was declared on.
			HidePropertiesRecursive(HidePropertiesRecursive, InPropertyName, InContainerClass->GetSuperClass());
			return;
		}

		DetailBuilder.HideProperty(PropHandleX);
		//if (DetailBuilder.IsPropertyVisible(PropHandleX)) {
		//	UE_LOG(LogCentralUIPluginEditor, VeryVerbose, TEXT("Failed to hide property: %s."), *InPropertyName);
		//}
		//else {
		//	UE_LOG(LogCentralUIPluginEditor, VeryVerbose, TEXT("Hid property: %s."), *InPropertyName);
		//}

		if (PropHandleX->HasMetaData(TEXT("ShowOnlyInnerProperties"))) {
			uint32 OutNum = 0;
			PropHandleX->GetNumChildren(OutNum);
			for (uint32 i = 0; i < OutNum; i++) {
				const TSharedPtr<IPropertyHandle> PropY = PropHandleX->GetChildHandle(i);
				if (!PropY->GetProperty()) {
					UE_LOG(LogCentralUIPluginEditor, Error, TEXT("invalid property: %s."), *PropY->GetPropertyDisplayName().ToString());
					continue;
				}

				const FString PropPath = FString(InPropertyName + "." + PropY->GetProperty()->GetName());
				HidePropertiesRecursive(HidePropertiesRecursive, PropPath, InContainerClass);
			}
		}
	};

	/** 
	* For all customized objects, see if the object is a centralized slate widget
	* , then initiate HidePropertiesRecursive for its managed properties. 
	*/
	for (const TWeakObjectPtr<UObject> ObjectX : OutObjects) {
		const ICentralSlateWidgetInterface* CentralObjectX = Cast<ICentralSlateWidgetInterface>(ObjectX);
		if (CentralObjectX == nullptr) {
			// Irrelevant object.
			continue;
		}

		for (const FString& NameX : CentralObjectX->GetCentralManagedPropertyNames()) {
			HidePropertiesRecursive(HidePropertiesRecursive, NameX, ObjectX->GetClass());
		}
	}
}

