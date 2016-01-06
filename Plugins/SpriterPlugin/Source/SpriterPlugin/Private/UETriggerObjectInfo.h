#pragma once

#include "Engine.h"
#include "objectinfo/triggerobjectinfo.h"

using namespace SpriterEngine;

class UETriggerObjectInfo : public TriggerObjectInfo
{
public:
	UETriggerObjectInfo(FString name);

	virtual void playTrigger() override;

private:
	FString name;
};
