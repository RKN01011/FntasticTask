// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Characters : ModuleRules
{
	public Characters(ReadOnlyTargetRules target) : base(target)
	{
		PublicDependencyModuleNames.AddRange(new[] 
			{ 
				"Core",      "CoreUObject",        "Engine", 
				"InputCore", "HeadMountedDisplay", "Niagara",
				"UMG",       "GameplayTasks",      "NavigationSystem",
				"AIModule"
			}
		);
		PrivateIncludePaths.AddRange(new[] { Name });
	}
}
