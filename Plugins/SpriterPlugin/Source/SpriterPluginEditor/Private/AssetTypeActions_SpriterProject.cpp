// Fill out your copyright notice in the Description page of Project Settings.

#include "SpriterPluginEditorPrivatePCH.h"
#include "SpriterProject.h"
#include "AssetTypeActions_SpriterProject.h"

UClass* FAssetTypeActions_SpriterProject::GetSupportedClass() const
{
	return USpriterProject::StaticClass();
}

void FAssetTypeActions_SpriterProject::GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const
{
	for (auto& Asset : TypeAssets)
	{
		const auto project = CastChecked<USpriterProject>(Asset);
		if (project->AssetImportData)
		{
			project->AssetImportData->ExtractFilenames(OutSourceFilePaths);
		}
	}
}
