// Fill out your copyright notice in the Description page of Project Settings.

#include "SpriterPluginPrivatePCH.h"
#include "SpriterProjectFactory.h"
#include "SpriterProject.h"
#include "AssetToolsModule.h"
#include "AssetRegistryModule.h"
#include "PackageTools.h"
#include "ObjectTools.h"


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
	result->Content = FString(fileContent);

	FAssetRegistryModule::AssetCreated(result);

	FEditorDelegates::OnAssetPostImport.Broadcast(this, result);
	return result;

}

#undef LOCTEXT_NAMESPACE