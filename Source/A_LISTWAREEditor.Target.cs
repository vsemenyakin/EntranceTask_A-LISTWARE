// All rights reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class A_LISTWAREEditorTarget : TargetRules
{
	public A_LISTWAREEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "A_LISTWARE" } );
	}
}
