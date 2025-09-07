/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#include "CentralUIPluginEditorUtils.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "PropertyEditorDelegates.h"
#include "UMGEditorProjectSettings.h" 
#include "Settings/ProjectPackagingSettings.h"
#include "Engine/AssetManagerSettings.h"
#include "LogCentralUIPluginEditor.h"


void UCentralUIPluginEditorUtils::RegisterCustomPropertyModuleClassLayout(const FName& InClassName, FOnGetDetailCustomizationInstance InDetailLayoutDelegate) {
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(InClassName, InDetailLayoutDelegate);
}

void UCentralUIPluginEditorUtils::HideWidgetOnUMGPalette(const FSoftClassPath& InWidgetClass) {
	UUMGEditorProjectSettings* Settings = GetMutableDefault<UUMGEditorProjectSettings>();
	check(IsValid(Settings));

	Settings->WidgetClassesToHide.AddUnique(InWidgetClass);
}

void UCentralUIPluginEditorUtils::ShowWidgetOnUMGPalette(const FSoftClassPath& InWidgetClass) {
	UUMGEditorProjectSettings* Settings = GetMutableDefault<UUMGEditorProjectSettings>();
	check(IsValid(Settings));

	Settings->WidgetClassesToHide.Remove(InWidgetClass);
}
