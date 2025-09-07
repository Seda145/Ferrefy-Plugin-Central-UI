/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PropertyEditorDelegates.h"
#include "Engine/EngineTypes.h"

#include "CentralUIPluginEditorUtils.generated.h"


UCLASS()
class CENTRALUIPLUGINEDITOR_API UCentralUIPluginEditorUtils : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:

	static void RegisterCustomPropertyModuleClassLayout(const FName& InClassName, FOnGetDetailCustomizationInstance InDetailLayoutDelegate);

	static void HideWidgetOnUMGPalette(const FSoftClassPath& InWidgetClass);

	static void ShowWidgetOnUMGPalette(const FSoftClassPath & InWidgetClass);

};

