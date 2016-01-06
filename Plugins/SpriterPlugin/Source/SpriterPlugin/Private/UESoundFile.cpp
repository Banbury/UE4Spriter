#include "SpriterPluginPrivatePCH.h"
#include "UESoundFile.h"

UESoundFile::UESoundFile(std::string initialFilePath) : SoundFile(initialFilePath)
{

}

SoundObjectInfoReference *UESoundFile::newSoundInfoReference()
{
	return NULL;
}