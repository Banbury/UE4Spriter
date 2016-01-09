// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpriterProject.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = (StaticMesh, Materials))
class SPRITERPLUGIN_API USpriterProject : public UObject
{
	GENERATED_BODY()

public:
	USpriterProject(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	FString Content;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, Instanced, Category = ImportSettings)
	class UAssetImportData* AssetImportData;

	virtual void PostInitProperties() override;
	virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;
	virtual void Serialize(FArchive& Ar) override;
#endif

};
