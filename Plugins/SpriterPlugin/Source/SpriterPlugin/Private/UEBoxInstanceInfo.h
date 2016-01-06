#pragma once

#include "objectinfo/boxinstanceinfo.h"

using namespace SpriterEngine;

class UEBoxInstanceInfo : public BoxInstanceInfo
{
public:
	UEBoxInstanceInfo(point initialSize);

	void render() override;
};
