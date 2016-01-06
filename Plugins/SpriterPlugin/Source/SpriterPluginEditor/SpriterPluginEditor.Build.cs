// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class SpriterPluginEditor : ModuleRules
{
    private string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    public SpriterPluginEditor(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"SpriterPluginEditor/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"SpriterPluginEditor/Private",
                "SpriterPlugin/Private",
				// ... add other private include paths required here ...
			}
            );
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "SpriterPlugin",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "Paper2D",
                "XmlParser",
                "Projects",
                "RHI",
                "RenderCore",
                "UnrealEd",
                "AssetTools",
				// ... add private dependencies that you statically link with here ...	
			}
            );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        LoadSpriterengine(Target);
    }

    public bool LoadSpriterengine(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "spriterengine", "lib");

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "spriterengine." + PlatformString + ".lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "spriterengine", "inc"));
        }

        Definitions.Add(string.Format("WITH_SPRITERENGINE_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
    }
