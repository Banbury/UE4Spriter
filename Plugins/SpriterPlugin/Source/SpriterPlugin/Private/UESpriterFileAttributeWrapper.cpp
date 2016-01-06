#include "SpriterPluginPrivatePCH.h"
#include "UESpriterFileAttributeWrapper.h"

FXmlAttribute2::FXmlAttribute2(FXmlAttribute* attr, FXmlNode* node, int index) : FXmlAttribute(attr->GetTag(), attr->GetValue())
{
	this->node = node;
	this->index = index;
}

FXmlAttribute2 *FXmlAttribute2::GetNextAttribute()
{
	if (index < node->GetAttributes().Num() - 1)
	{
		FXmlAttribute attr = node->GetAttributes()[index + 1];
		return new FXmlAttribute2(&attr, node, index + 1);
	}
	return 0;
}


UESpriterFileAttributeWrapper::UESpriterFileAttributeWrapper(FXmlAttribute2 *attr) : SpriterFileAttributeWrapper()
{
	this->attr = attr;
}

std::string UESpriterFileAttributeWrapper::getName()
{
	if (isValid()) {
		return TCHAR_TO_ANSI(*attr->GetTag());
	}
	return "";
}

bool UESpriterFileAttributeWrapper::isValid()
{
	return (attr != NULL);
}

real UESpriterFileAttributeWrapper::getRealValue()
{
	if (isValid() && attr->GetValue().IsNumeric())
	{
		real f = FCString::Atof(*attr->GetValue());
		return f;
	}
	return 0;
}

int UESpriterFileAttributeWrapper::getIntValue()
{
	if (isValid() && attr->GetValue().IsNumeric())
	{
		int n = FCString::Atoi(*attr->GetValue());
		return n;
	}
	return 0;
}

std::string UESpriterFileAttributeWrapper::getStringValue()
{
	if (isValid()) {
		return TCHAR_TO_ANSI(*attr->GetValue());
	}
	return "";
}

void UESpriterFileAttributeWrapper::advanceToNextAttribute()
{
	if (isValid()) {
		attr = attr->GetNextAttribute();
	}
}
