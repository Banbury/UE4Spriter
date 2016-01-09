#include "SpriterPluginPrivatePCH.h"
#include "UETriggerObjectInfo.h"

UETriggerObjectInfo::UETriggerObjectInfo(FString name) : TriggerObjectInfo()
{
	this->name = name;
}

void UETriggerObjectInfo::playTrigger()
{
	TriggerObjectInfo::playTrigger();
}
