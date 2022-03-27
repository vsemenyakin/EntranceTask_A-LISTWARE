// All rights reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class A_LISTWARETarget : TargetRules
{
	public A_LISTWARETarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "A_LISTWARE" } );
	}
}
