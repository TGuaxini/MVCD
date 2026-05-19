// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MVCD_Unreal : ModuleRules
{
	public MVCD_Unreal(ReadOnlyTargetRules Target) : base(Target)
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
			"MVCD_Unreal",
			"MVCD_Unreal/Variant_Horror",
			"MVCD_Unreal/Variant_Horror/UI",
			"MVCD_Unreal/Variant_Shooter",
			"MVCD_Unreal/Variant_Shooter/AI",
			"MVCD_Unreal/Variant_Shooter/UI",
			"MVCD_Unreal/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
