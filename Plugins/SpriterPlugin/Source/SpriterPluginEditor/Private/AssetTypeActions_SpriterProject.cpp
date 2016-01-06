// Fill out your copyright notice in the Description page of Project Settings.

#include "SpriterPluginEditorPrivatePCH.h"
#include "SpriterProject.h"
#include "AssetTypeActions_SpriterProject.h"

UClass* FAssetTypeActions_SpriterProject::GetSupportedClass() const
{
	return USpriterProject::StaticClass();
}

