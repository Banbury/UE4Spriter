#include "SpriterPluginPrivatePCH.h"
#include "UESpriterFileElementWrapper.h"
#include "UESpriterFileAttributeWrapper.h"

UESpriterFileElementWrapper::UESpriterFileElementWrapper(FXmlNode *node) : SpriterFileElementWrapper()
{
	this->node = node;
}

std::string UESpriterFileElementWrapper::getName()
{
	return TCHAR_TO_ANSI(*node->GetTag());
}

bool UESpriterFileElementWrapper::isValid()
{
	return (node != NULL);
}

void UESpriterFileElementWrapper::advanceToNextSiblingElement()
{
	node = const_cast<FXmlNode*>(node->GetNextNode());
}

void UESpriterFileElementWrapper::advanceToNextSiblingElementOfSameName()
{
	FXmlNode *sibling = node;
	while ((sibling = const_cast<FXmlNode*>(sibling->GetNextNode())) != NULL)
	{ 
		if (sibling->GetTag().Equals(node->GetTag()))
		{
			node = sibling;
			return;
		}
	}
	node = NULL;
}

SpriterFileAttributeWrapper *UESpriterFileElementWrapper::newAttributeWrapperFromFirstAttribute()
{
	TArray<FXmlAttribute> attrs = node->GetAttributes();
	if (attrs.Num() > 0)
	{
		return new UESpriterFileAttributeWrapper(new FXmlAttribute2(const_cast<FXmlAttribute *>(&attrs[0]), node, 0));
	}
	return new UESpriterFileAttributeWrapper(0);
}

SpriterFileAttributeWrapper *UESpriterFileElementWrapper::newAttributeWrapperFromFirstAttribute(const std::string & attributeName)
{
	TArray<FXmlAttribute> attrs = node->GetAttributes();

	for (int i = 0; i < attrs.Num(); i++)
	{
		if (attrs[i].GetTag().Equals(ANSI_TO_TCHAR(attributeName.c_str())))
		{
			return new UESpriterFileAttributeWrapper(new FXmlAttribute2(const_cast<FXmlAttribute *>(&attrs[i]), node, i));
		}
	}

	return new UESpriterFileAttributeWrapper(0);
}

SpriterFileElementWrapper *UESpriterFileElementWrapper::newElementWrapperFromFirstElement()
{
	return new UESpriterFileElementWrapper(const_cast<FXmlNode*>(node->GetFirstChildNode()));
}

SpriterFileElementWrapper *UESpriterFileElementWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
{
	return new UESpriterFileElementWrapper(node->FindChildNode(ANSI_TO_TCHAR(elementName.c_str())));
}

SpriterFileElementWrapper *UESpriterFileElementWrapper::newElementWrapperFromNextSiblingElement()
{
	return new UESpriterFileElementWrapper(const_cast<FXmlNode*>(node->GetNextNode()));
}

SpriterFileElementWrapper *UESpriterFileElementWrapper::newElementClone()
{
	return new UESpriterFileElementWrapper(node);
}

