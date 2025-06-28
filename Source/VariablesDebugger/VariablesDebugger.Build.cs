// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VariablesDebugger : ModuleRules
{
	public VariablesDebugger(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				// your existing paths…
				"Runtime/UMG/Public",        // <— makes “Blueprint/UserWidget.h” visible
				"Runtime/Slate/Public",
				"Editor/PropertyEditor/Public"

			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				"VariablesDebugger/Private",
				"VariablesDebugger/Private/Settings"
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"DeveloperSettings",
				"UMG",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"ToolMenus"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
                "UMG",
                "Slate",
                "SlateCore"

				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
