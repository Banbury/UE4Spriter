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
};
