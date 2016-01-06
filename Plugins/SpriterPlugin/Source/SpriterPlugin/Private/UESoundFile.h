#pragma once

#include "override/soundfile.h"

using namespace SpriterEngine;

class UESoundFile : public SoundFile
{
public:
	UESoundFile(std::string initialFilePath);

	SoundObjectInfoReference *newSoundInfoReference() override;
};
