#pragma once

#include "objectinfo/boneinstanceinfo.h"

using namespace SpriterEngine;

class UEBoneInstanceInfo : public BoneInstanceInfo
{
public:
	UEBoneInstanceInfo(point initialSize);

	void render() override;
};
