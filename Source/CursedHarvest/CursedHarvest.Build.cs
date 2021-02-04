// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CursedHarvest : ModuleRules
{
	public CursedHarvest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
