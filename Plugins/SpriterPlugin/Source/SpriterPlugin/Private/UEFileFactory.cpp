#include "SpriterPluginPrivatePCH.h"
#include "UEFileFactory.h"
#include "UEImageFile.h"
#include "UESoundFile.h"
#include "UESpriterFileDocumentWrapper.h"

UEFileFactory::UEFileFactory(FString basePath, UCanvas *canvas, FString imagePath) : FileFactory()
{
	this->canvas = canvas;
	this->basePath = basePath;
	this->imagePath = imagePath;
	FPaths::NormalizeFilename(this->basePath);
}

ImageFile *UEFileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot)
{
	FString relPath = ANSI_TO_TCHAR(initialFilePath.c_str());
	CleanPath(relPath);
	return new UEImageFile(TCHAR_TO_ANSI(*relPath), initialDefaultPivot, canvas, imagePath);
}

SoundFile *UEFileFactory::newSoundFile(const std::string &initialFilePath)
{
	FString relPath = ANSI_TO_TCHAR(initialFilePath.c_str());
	CleanPath(relPath);
	return new UESoundFile(TCHAR_TO_ANSI(*relPath));
}

SpriterFileDocumentWrapper *UEFileFactory::newScmlDocumentWrapper()
{
	return new UESpriterFileDocumentWrapper();
}

void UEFileFactory::CleanPath(FString &path)
{
	if (!path.IsEmpty())
	{
		FPaths::NormalizeFilename(path);
		path.RemoveFromStart(basePath);
		path.RemoveFromStart(TEXT("/"));
		path.RemoveFromEnd(FPaths::GetExtension(path, true));
	}
}
