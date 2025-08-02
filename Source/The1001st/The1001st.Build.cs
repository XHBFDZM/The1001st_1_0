// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class The1001st : ModuleRules
{
	public The1001st(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","GameplayTags","GameplayTasks", "UMG" });

        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UnrealEd", "TextureCompressor", "Chaos" });

        PublicDependencyModuleNames.AddRange(new string[] { "NavigationSystem" });
    }
}
