// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetTypeActions_Base.h"
#include "Editor/UnrealEd/Classes/Settings/EditorLoadingSavingSettings.h"

/**
 * 
 */
class SPRITERPLUGIN_API FAssetTypeActions_SpriterProject : public FAssetTypeActions_Base
{
public:
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return FText::FromString("Spriter Project"); }
	virtual FColor GetTypeColor() const override { return FColor(153, 101, 249); }
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }

};
