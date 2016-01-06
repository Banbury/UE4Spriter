#pragma once

#include "override/objectfactory.h"

using namespace SpriterEngine;

class UEObjectFactory : public ObjectFactory
{
public:
	UEObjectFactory();

	virtual PointInstanceInfo *newPointInstanceInfo() override;

	virtual BoxInstanceInfo *newBoxInstanceInfo(point size) override;

	virtual BoneInstanceInfo *newBoneInstanceInfo(point size) override;

	virtual TriggerObjectInfo *newTriggerObjectInfo(std::string triggerName) override;
};
