#pragma once

#include "override/filefactory.h"

using namespace SpriterEngine;

class UEFileFactory : public FileFactory
{
public:
	UEFileFactory(FString basePath, UCanvas *canvas, FString imagePath);

	ImageFile *newImageFile(const std::string &initialFilePath, point initialDefaultPivot) override;

	SoundFile *newSoundFile(const std::string &initialFilePath) override;

	SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;

private:
	UCanvas *canvas;
	FString imagePath;
	FString basePath;

	void CleanPath(FString &path);
};
