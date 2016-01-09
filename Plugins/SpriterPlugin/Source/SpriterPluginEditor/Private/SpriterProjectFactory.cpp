// Fill out your copyright notice in the Description page of Project Settings.

#include "SpriterPluginEditorPrivatePCH.h"
#include "SpriterProjectFactory.h"
#include "SpriterProject.h"
#include "AssetToolsModule.h"
#include "AssetRegistryModule.h"
#include "PackageTools.h"
#include "ObjectTools.h"
#include "CoreMisc.h"


#define LOCTEXT_NAMESPACE "SpriterProject"

USpriterProjectFactory::USpriterProjectFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = false;
	//bEditAfterNew = true;
	bEditorImport = true;
	bText = true;
	SupportedClass = USpriterProject::StaticClass();
	Formats.Add(TEXT("scml;Spriter Project"));
}

UObject* USpriterProjectFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	USpriterProject* NewObjectAsset = NewObject<USpriterProject>(InParent, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

bool USpriterProjectFactory::FactoryCanImport(const FString & Filename)
{
	return FPaths::GetExtension(Filename).Equals(TEXT("scml"), ESearchCase::IgnoreCase);
}

UObject* USpriterProjectFactory::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn)
{
	Flags |= RF_Transactional;
	FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);

	const FString filename = UFactory::GetCurrentFilename();
	FString sourcePath;
	FString baseFilename;
	FString extension;
	FPaths::Split(CurrentFilename, sourcePath, baseFilename, extension);

	const FString packagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetPathName());

	USpriterProject* result = nullptr;
	const FString fileContent(BufferEnd - Buffer, Buffer);

	const FString sanitizedPackageName = PackageTools::SanitizePackageName(packagePath + TEXT("/") + baseFilename);
	FString defaultSuffix;
	FString assetName;
	FString packageName;
	FAssetToolsModule& assetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	assetToolsModule.Get().CreateUniqueAssetName(sanitizedPackageName, defaultSuffix, packageName, assetName);

	UObject *OuterForFrame = CreatePackage(nullptr, *packageName);

	result = NewObject<USpriterProject>(OuterForFrame, *assetName, Flags);
	if (result != NULL)
	{
		result->Content = FString(fileContent);
		result->AssetImportData->Update(CurrentFilename);
		FAssetRegistryModule::AssetCreated(result);
	}

	FEditorDelegates::OnAssetPostImport.Broadcast(this, result);
	return result;

}

bool USpriterProjectFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	USpriterProject* project = Cast<USpriterProject>(Obj);
	if (project && project->AssetImportData)
	{
		project->AssetImportData->ExtractFilenames(OutFilenames);
		return true;
	}
	return false;
}

void USpriterProjectFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	USpriterProject* project = Cast<USpriterProject>(Obj);
	if (project && ensure(NewReimportPaths.Num() == 1))
	{
		project->AssetImportData->UpdateFilenameOnly(NewReimportPaths[0]);
	}
}

EReimportResult::Type USpriterProjectFactory::Reimport(UObject* Obj)
{
	USpriterProject* project = Cast<USpriterProject>(Obj);
	if (!project)
	{
		return EReimportResult::Failed;
	}

	const FString filename = project->AssetImportData->GetFirstFilename();
	if (!filename.Len() || IFileManager::Get().FileSize(*filename) == INDEX_NONE)
	{
		return EReimportResult::Failed;
	}

	FString content;
	if (FFileHelper::LoadFileToString(content, *filename))
	{
		project->Content = content;
		project->AssetImportData->Update(filename);

		if (project->GetOuter())
		{
			project->GetOuter()->MarkPackageDirty();
		}
		else
		{
			project->MarkPackageDirty();
		}
		return EReimportResult::Succeeded;
	}
	else
	{
		return EReimportResult::Failed;
	}
}

int32 USpriterProjectFactory::GetPriority() const
{
	return ImportPriority;
}


#undef LOCTEXT_NAMESPACE