#pragma once

#include "spriterengine.h"
#include "override/imagefile.h"

using namespace SpriterEngine;

class UEImageFile : public ImageFile
{
public:
	UEImageFile(std::string initialFilePath, point initialDefaultPivot, UCanvas *canvas, FString imagePath);
	~UEImageFile();

	void renderSprite(UniversalObjectInterface *spriteInfo) override;

private:
	UCanvas *canvas;
	FString imagePath;
	UTexture2D *texture;
	int width;
	int height;

	void createSprite();
};
