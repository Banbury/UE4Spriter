// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "spriterengine.h"
#include "SpriterRenderTarget2D.h"
#include "SpriterProject.h"
#include "SpriterComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = (StaticMesh, Materials))
class SPRITERPLUGIN_API USpriterComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	USpriterComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TextureSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpriterProject *SpriterProject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShortTooltip = "Folder containing sprites."))
	FString Sprites;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Animation;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic *materialInst;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Spriter")
	void ApplyCharacterMap(FString mapName);

	UFUNCTION(BlueprintCallable, Category = "Spriter")
	void RemoveCharacterMap(FString mapName);

	UFUNCTION(BlueprintCallable, Category = "Spriter")
	void RemoveAllCharacterMaps();

	UFUNCTION(BlueprintCallable, Category = "Spriter")
	void PlayAnimation();

	UFUNCTION(BlueprintCallable, Category = "Spriter")
	void StopAnimation();

private:
	UPROPERTY(Transient)
	USpriterRenderTarget2D *canvas;

	void CreateTexture();
};
