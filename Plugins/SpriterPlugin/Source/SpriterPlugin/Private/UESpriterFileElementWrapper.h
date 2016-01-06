#pragma once

#include "override/spriterfileelementwrapper.h"
#include "XmlFile.h"

using namespace SpriterEngine;

class UESpriterFileElementWrapper : public SpriterFileElementWrapper
{
public:
	UESpriterFileElementWrapper(FXmlNode *node);

	std::string getName() override;

	bool isValid() override;

	void advanceToNextSiblingElement() override;
	void advanceToNextSiblingElementOfSameName() override;

private:
	SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute() override;
	SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute(const std::string & attributeName) override;

	SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
	SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

	SpriterFileElementWrapper *newElementWrapperFromNextSiblingElement() override;

	SpriterFileElementWrapper *newElementClone() override;

	FXmlNode *node;
};
