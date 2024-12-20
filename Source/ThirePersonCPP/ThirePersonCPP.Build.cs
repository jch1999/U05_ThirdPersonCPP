// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ThirePersonCPP : ModuleRules
{
	public ThirePersonCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"UMG",
			"AIModule",
			"GameplayTasks"
		});
	}
}
