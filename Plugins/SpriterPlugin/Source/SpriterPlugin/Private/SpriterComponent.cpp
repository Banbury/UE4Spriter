// Fill out your copyright notice in the Description page of Project Settings.

#include "SpriterPluginPrivatePCH.h"
#include "SpriterComponent.h"
#include "SpriterRenderTarget2D.h"
#include "UEFileFactory.h"
#include "UEObjectFactory.h"
#include "UEImageFile.h"
#include "UESoundFile.h"


USpriterComponent::USpriterComponent(const FObjectInitializer& ObjectInitializer) : UStaticMeshComponent(ObjectInitializer)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> m(TEXT("/SpriterPlugin/Meshes/plane"));
	StaticMesh = m.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> mat(TEXT("/SpriterPlugin/Materials/SpriterMaterial"));
	SetMaterial(0, mat.Object);

	TextureSize = FVector2D(1024, 1024);
	Sprites = TEXT("/Game/Sprites");
}

// Called when the game starts
void USpriterComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateTexture();

	materialInst = CreateAndSetMaterialInstanceDynamic(0);
	materialInst->SetTextureParameterValue(TEXT("DiffuseTexture"), canvas);

	if (SpriterProject != NULL)
	{
		FStringAssetReference path(SpriterProject);
		canvas->loadModel(path.ToString(), Sprites);
	}
}


// Called every frame
void USpriterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	canvas->setAnimation(Animation);
	canvas->UpdateResource(DeltaTime);
}

void USpriterComponent::CreateTexture()
{
	canvas = USpriterRenderTarget2D::CreateSpriterRenderTarget2D(this, USpriterRenderTarget2D::StaticClass(), TextureSize.X, TextureSize.Y);
	canvas->UpdateResource(0);
}

void USpriterComponent::ApplyCharacterMap(FString mapName)
{
	if (canvas != NULL)
	{
		canvas->applyCharacterMap(mapName);
	}
}

void USpriterComponent::RemoveCharacterMap(FString mapName)
{
	if (canvas != NULL)
	{
		canvas->removeCharacterMap(mapName);
	}
}

void USpriterComponent::RemoveAllCharacterMaps()
{
	if (canvas != NULL)
	{
		canvas->removeAllCharacterMaps();
	}
}

void USpriterComponent::SetAnimation(FString name, float blendTime)
{
	if (canvas != NULL)
	{
		canvas->setAnimation(name, blendTime);
		Animation = name;
	}
}

void USpriterComponent::PlayAnimation()
{
	if (canvas != NULL)
	{
		canvas->startPlayback();
	}
}

void USpriterComponent::StopAnimation()
{
	if (canvas != NULL)
	{
		canvas->stopPlayBack();
	}
}

int32 USpriterComponent::GetTriggerCount(FString name)
{
	if (canvas != NULL)
	{
		return canvas->getTriggerCount(name);
	}
	return 0;
}