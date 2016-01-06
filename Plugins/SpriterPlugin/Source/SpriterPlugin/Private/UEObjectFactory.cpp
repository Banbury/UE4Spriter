#include "SpriterPluginPrivatePCH.h"
#include "UEObjectFactory.h"

#include "UEPointInstanceInfo.h"
#include "UEBoxInstanceInfo.h"
#include "UEBoneInstanceInfo.h"
#include "UETriggerObjectInfo.h"

UEObjectFactory::UEObjectFactory() : ObjectFactory()
{

}

PointInstanceInfo *UEObjectFactory::newPointInstanceInfo()
{
	return new PointInstanceInfo();
}

BoxInstanceInfo *UEObjectFactory::newBoxInstanceInfo(point size)
{
	return new UEBoxInstanceInfo(size);
}

BoneInstanceInfo *UEObjectFactory::newBoneInstanceInfo(point size)
{
	return new UEBoneInstanceInfo(size);
}

TriggerObjectInfo *UEObjectFactory::newTriggerObjectInfo(std::string triggerName)
{
	return new UETriggerObjectInfo(ANSI_TO_TCHAR(triggerName.c_str()));
}