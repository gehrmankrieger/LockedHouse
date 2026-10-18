// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LockedHouse : ModuleRules
{
	public LockedHouse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"LockedHouse",
			"LockedHouse/Variant_Platforming",
			"LockedHouse/Variant_Platforming/Animation",
			"LockedHouse/Variant_Combat",
			"LockedHouse/Variant_Combat/AI",
			"LockedHouse/Variant_Combat/Animation",
			"LockedHouse/Variant_Combat/Gameplay",
			"LockedHouse/Variant_Combat/Interfaces",
			"LockedHouse/Variant_Combat/UI",
			"LockedHouse/Variant_SideScrolling",
			"LockedHouse/Variant_SideScrolling/AI",
			"LockedHouse/Variant_SideScrolling/Gameplay",
			"LockedHouse/Variant_SideScrolling/Interfaces",
			"LockedHouse/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
