// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Weast : ModuleRules
{
	public Weast(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                // ... add public include paths required here ...
                Path.Combine(ModuleDirectory, "Classes")
            }
        );


		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
                "CoreUObject",
				"DeveloperSettings",
            });

		PrivateDependencyModuleNames.AddRange(
			new string[] {
                "Projects",
				"Engine",
				"Slate",
				"SlateCore", 
				"MessageLog",
				"HTTP",
				"Json",
                "JsonUtilities",
                "Serialization"
            });


        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd"
                });
        }
    }
}
