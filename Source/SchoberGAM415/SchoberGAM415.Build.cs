// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SchoberGAM415 : ModuleRules
{
	public SchoberGAM415(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
