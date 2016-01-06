#include "SpriterPluginPrivatePCH.h"
#include "UEImageFile.h"


UEImageFile::UEImageFile(std::string initialFilePath, point initialDefaultPivot, UCanvas *canvas, FString imagePath) : ImageFile(initialFilePath, initialDefaultPivot)
{
	this->canvas = canvas;
	this->imagePath = imagePath;
	createSprite();
}

UEImageFile::~UEImageFile()
{
}

void UEImageFile::renderSprite(SpriterEngine::UniversalObjectInterface *spriteInfo)
{
	if (texture != NULL)
	{
		point p = spriteInfo->getPosition();
		real angle = FMath::RadiansToDegrees(spriteInfo->getAngle());
		point s = spriteInfo->getScale();
		point pivot = spriteInfo->getPivot();
		FLinearColor drawColor = FLinearColor(1, 1, 1, spriteInfo->getAlpha());

		canvas->K2_DrawTexture(texture, FVector2D(p.x + canvas->SizeX / 2 - pivot.x * width, p.y + canvas->SizeY / 2 - pivot.y * height), FVector2D(width * s.x, height * s.y), FVector2D(0, 0), FVector2D::UnitVector, drawColor, EBlendMode::BLEND_Masked, angle, FVector2D(pivot.x, pivot.y));
	}
}

void UEImageFile::createSprite()
{
	texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FPaths::Combine(*imagePath, ANSI_TO_TCHAR(path().c_str()))));
	if (texture != NULL)
	{
		width = texture->GetSizeX();
		height = texture->GetSizeY();
	}
}
