/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
using System.IO;
using UnrealBuildTool;


public class CentralUIPlugin : ModuleRules {
	public CentralUIPlugin(ReadOnlyTargetRules Target) : base(Target) {
		PrivatePCHHeaderFile = "Public/CentralUIPlugin.h";
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		OptimizeCode = CodeOptimization.InShippingBuildsOnly;
		IWYUSupport = IWYUSupport.Full;

		// While testing if all headers are included properly, set the following:
		// PCHUsage = PCHUsageMode.NoSharedPCHs;
		// bUseUnity = false;

		IncludeSubDirectoriesRecursive(ModuleDirectory + "\\Private", true);
		IncludeSubDirectoriesRecursive(ModuleDirectory + "\\Public", false);
		
		PrivateDependencyModuleNames.AddRange(new string[] {

		});

		PublicDependencyModuleNames.AddRange(new string[] {
			"AdvancedWidgets"
			, "Core"
			, "CoreUObject"
			, "DeveloperSettings"
			, "Engine"
			, "UMG"
			, "Slate"
			, "SlateCore"
		});
	}

	private void IncludeSubDirectoriesRecursive(string DirectoryPathToSearch, bool bIsPrivate) {
		foreach (string DirectoryPath in Directory.GetDirectories(DirectoryPathToSearch)) {
			if (bIsPrivate) {
				PrivateIncludePaths.Add(DirectoryPath);
			}
			else {
				PublicIncludePaths.Add(DirectoryPath);
			}
			IncludeSubDirectoriesRecursive(DirectoryPath, bIsPrivate);
		}
	}
}
