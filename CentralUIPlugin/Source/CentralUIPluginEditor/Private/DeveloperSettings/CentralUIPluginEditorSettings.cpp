/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#include "CentralUIPluginEditorSettings.h"
#include "CentralUIPluginEditorInstaller.h"


void UCentralUIPluginEditorSettings::PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) {
	Super::PostEditChangeProperty(InPropertyChangedEvent);

	if (!InPropertyChangedEvent.Property || InPropertyChangedEvent.Property->GetFName() != TEXT("bHideReplacedSlateWidgetPalette")) {
		return;
	}

	FCentralUIPluginEditorInstaller CentralUIPluginEditorInstaller = FCentralUIPluginEditorInstaller();
	if (bHideReplacedSlateWidgetPalette) {
		CentralUIPluginEditorInstaller.HideReplacedSlateWidgetPalette();
	}
	else {
		CentralUIPluginEditorInstaller.ShowReplacedSlateWidgetPalette();
	}
}