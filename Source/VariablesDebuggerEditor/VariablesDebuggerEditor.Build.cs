using UnrealBuildTool;

public class VariablesDebuggerEditor : ModuleRules
{
	public VariablesDebuggerEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"VariablesDebugger" // Only your own runtime module needs to be public
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			"EditorStyle",
			"PropertyEditor",
			"ToolWidgets",
			"EditorWidgets"      // ✅ Needed for SSearchableComboBox
		});
	}
}