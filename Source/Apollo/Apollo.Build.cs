// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Apollo : ModuleRules
{
	public Apollo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput", 
			"UMG",
			"DatabaseSupport", 
			"SQLiteCore", 
			"SQLiteSupport"
		});
	}
}
