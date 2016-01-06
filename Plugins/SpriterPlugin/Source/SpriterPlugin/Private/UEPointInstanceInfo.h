#pragma once

#include "objectinfo/pointinstanceinfo.h"

using namespace SpriterEngine;

class UEPointInstanceInfo : public PointInstanceInfo
{
public:
	UEPointInstanceInfo();

	void render() override;
};
