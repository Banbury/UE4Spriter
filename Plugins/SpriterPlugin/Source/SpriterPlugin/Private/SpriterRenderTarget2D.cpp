// Fill out your copyright notice in the Description page of Project Settings.

#include "SpriterPluginPrivatePCH.h"
#include "SpriterRenderTarget2D.h"
#include "UEFileFactory.h"
#include "UEObjectFactory.h"
#include "UEImageFile.h"
#include "UESoundFile.h"

USpriterRenderTarget2D::USpriterRenderTarget2D(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	World(nullptr)
{
	bNeedsTwoCopies = false;
	canvas = NewObject<UCanvas>(GetTransientPackage());
	canvas->AddToRoot();
}


void USpriterRenderTarget2D::UpdateResource(float deltaTime)
{
	Super::UpdateResource();

	if (IsTemplate())
	{
		return;
	}

	if (canvas == nullptr)
	{
		canvas = NewObject<UCanvas>(GetTransientPackage());
		canvas->AddToRoot();
	}

	canvas->Init(GetSurfaceWidth(), GetSurfaceHeight(), nullptr);
	canvas->Update();

	// Update the resource immediately to remove it from the deferred resource update list. This prevents the texture
	// from being cleared each frame.
	UpdateResourceImmediate();

	// Enqueue the rendering command to set up the rendering canvas.
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			CanvasRenderTargetMakeCurrentCommand,
			FTextureRenderTarget2DResource*,
			TextureRenderTarget,
			(FTextureRenderTarget2DResource*)GameThread_GetRenderTargetResource(),
			{
				SetRenderTarget(RHICmdList, TextureRenderTarget->GetRenderTargetTexture(), FTexture2DRHIRef());
				RHICmdList.SetViewport(0, 0, 0.0f, TextureRenderTarget->GetSizeXY().X, TextureRenderTarget->GetSizeXY().Y, 1.0f);
			}
	);

	// Create the FCanvas which does the actual rendering.
	const UWorld* WorldPtr = World.Get();
	const ERHIFeatureLevel::Type FeatureLevel = WorldPtr != nullptr ? World->FeatureLevel : GMaxRHIFeatureLevel;
	FCanvas RenderCanvas(GameThread_GetRenderTargetResource(), nullptr, FApp::GetCurrentTime() - GStartTime, FApp::GetDeltaTime(), FApp::GetCurrentTime() - GStartTime, FeatureLevel);
	canvas->Canvas = &RenderCanvas;

	render(deltaTime);
	// Clean up and flush the rendering canvas.
	canvas->Canvas = nullptr;
	RenderCanvas.Flush_GameThread();

	// Enqueue the rendering command to copy the freshly rendering texture resource back to the render target RHI 
	// so that the texture is updated and available for rendering.
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			CanvasRenderTargetResolveCommand,
			FTextureRenderTargetResource*,
			RenderTargetResource,
			GameThread_GetRenderTargetResource(),
			{
				RHICmdList.CopyToResolveTarget(RenderTargetResource->GetRenderTargetTexture(), RenderTargetResource->TextureRHI, true, FResolveParams());
			}
	);

}

USpriterRenderTarget2D* USpriterRenderTarget2D::CreateSpriterRenderTarget2D(UObject* WorldContextObject, TSubclassOf<USpriterRenderTarget2D> SpriterRenderTarget2DClass, int32 Width, int32 Height)
{
	if ((Width > 0) && (Height > 0) && (SpriterRenderTarget2DClass != NULL))
	{
		USpriterRenderTarget2D* NewSpriterRenderTarget = NewObject<USpriterRenderTarget2D>(GetTransientPackage(), SpriterRenderTarget2DClass);
		if (NewSpriterRenderTarget)
		{
			NewSpriterRenderTarget->World = GEngine->GetWorldFromContextObject(WorldContextObject);
			NewSpriterRenderTarget->InitAutoFormat(Width, Height);
			NewSpriterRenderTarget->ClearColor = FLinearColor(0, 0, 0, 0);
			return NewSpriterRenderTarget;
		}
	}

	return nullptr;
}

void USpriterRenderTarget2D::GetSize(int32& Width, int32& Height)
{
	Width = GetSurfaceWidth();
	Height = GetSurfaceHeight();
}


UWorld* USpriterRenderTarget2D::GetWorld() const
{
	return World.Get();
}

void USpriterRenderTarget2D::loadModel(FString path, FString imagePath)
{
	model = new SpriterEngine::SpriterModel(new UEFileFactory(FPaths::GetPath(path), canvas, imagePath), new UEObjectFactory());
	if (model != NULL)
	{
		model->loadFileSCML(TCHAR_TO_ANSI(*path));
		entity = model->getNewEntityInstance(0);
	}
}

void USpriterRenderTarget2D::setAnimation(FString name)
{
	if (entity != NULL && !name.Equals(currentAnimation))
	{
		entity->setCurrentAnimation(TCHAR_TO_ANSI(*name));
		currentAnimation = name;
	}
}

void USpriterRenderTarget2D::render(float deltaTime)
{
	if (entity != NULL)
	{
		entity->setTimeElapsed(deltaTime * 1000);
		entity->render();
	}
}

void USpriterRenderTarget2D::applyCharacterMap(FString mapName)
{
	if (entity != NULL)
	{
		entity->applyCharacterMap(TCHAR_TO_ANSI(*mapName));
	}
}

void USpriterRenderTarget2D::removeCharacterMap(FString mapName)
{
	if (entity != NULL)
	{
		entity->removeCharacterMap(TCHAR_TO_ANSI(*mapName));
	}
}

void USpriterRenderTarget2D::removeAllCharacterMaps()
{
	if (entity != NULL)
	{
		entity->removeAllCharacterMaps();
	}
}

void USpriterRenderTarget2D::startPlayback()
{
	if (entity != NULL)
	{
		entity->startResumePlayback();
	}
}

void USpriterRenderTarget2D::stopPlayBack()
{
	if (entity != NULL)
	{
		entity->pausePlayback();
	}
}
