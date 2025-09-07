/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#include "CentralUIPluginEditor.h"
#include "CentralUIPluginEditorInstaller.h"
#include "Modules/ModuleManager.h"


void FCentralUIPluginEditorModule::StartupModule() {
	FCentralUIPluginEditorInstaller Installer = FCentralUIPluginEditorInstaller();
	Installer.RunAutomatedInstaller();
}



IMPLEMENT_MODULE(FCentralUIPluginEditorModule, CentralUIPluginEditor)