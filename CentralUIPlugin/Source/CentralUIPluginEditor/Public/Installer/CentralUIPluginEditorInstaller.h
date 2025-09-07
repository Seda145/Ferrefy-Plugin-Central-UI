/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "UObject/SoftObjectPath.h"


class FCentralUIPluginEditorInstaller {
	
private:

protected:

public:

private:

protected:

public:
	
	// Setup

	void RunAutomatedInstaller();

	TArray<FSoftClassPath> GetSlateWidgetsToHide() const;

	// Hide slate widgets that have been implemented by this plugin on the editor's widget pallet.
	void HideReplacedSlateWidgetPalette() const;
	
	// Unhide any installed edit which hides the default slate widgets.
	void ShowReplacedSlateWidgetPalette() const;

	void RegisterDetailPanels() const;


};