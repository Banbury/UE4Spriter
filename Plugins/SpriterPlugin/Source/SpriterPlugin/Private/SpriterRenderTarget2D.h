// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TextureRenderTarget2D.h"
#include "spriterengine.h"
#include "SpriterRenderTarget2D.generated.h"

/**
 * 
 */
UCLASS()
class SPRITERPLUGIN_API USpriterRenderTarget2D : public UTextureRenderTarget2D
{
	GENERATED_BODY()
	
	
public:
	USpriterRenderTarget2D(const FObjectInitializer& ObjectInitializer);

	virtual void UpdateResource(float deltaTime);
	static USpriterRenderTarget2D* CreateSpriterRenderTarget2D(UObject* WorldContextObject, TSubclassOf<USpriterRenderTarget2D> SpriterRenderTarget2DClass, int32 Width = 1024, int32 Height = 1024);
	void GetSize(int32& Width, int32& Height);
	virtual UWorld* GetWorld() const override;

	void loadModel(FString path, FString imagePath);
	void setAnimation(FString name);

	UPROPERTY()
	UCanvas *canvas;

	void applyCharacterMap(FString mapName);
	void removeCharacterMap(FString mapName);
	void removeAllCharacterMaps();
	void startPlayback();
	void stopPlayBack();

protected:
	UPROPERTY()
	TWeakObjectPtr<UWorld> World;

private:
	SpriterEngine::SpriterModel *model;
	SpriterEngine::EntityInstance *entity;

	FString currentAnimation;

	void render(float deltaTime);

};
