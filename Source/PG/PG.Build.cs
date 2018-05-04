// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.


using UnrealBuildTool;

public class PG : ModuleRules
{
	public PG(ReadOnlyTargetRules rules) : base(rules)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
