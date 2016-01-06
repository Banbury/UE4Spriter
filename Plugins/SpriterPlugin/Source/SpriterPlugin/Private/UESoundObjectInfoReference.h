#pragma once

#include "override/soundobjectinforeference.h"

using namespace SpriterEngine;

class UESoundObjectInfoReference : public SoundObjectInfoReference
{
public:
	UESoundObjectInfoReference();

	void playTrigger() override;
};
