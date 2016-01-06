#pragma once

#include "override/spriterfileattributewrapper.h"
#include "XmlFile.h"

using namespace SpriterEngine;

class FXmlAttribute2 : public FXmlAttribute
{
public:
	FXmlAttribute2(FXmlAttribute* attr, FXmlNode* node, int index);
	FXmlAttribute2 *GetNextAttribute();

private:
	FXmlNode *node;
	int index;
};

class UESpriterFileAttributeWrapper : public SpriterFileAttributeWrapper
{
public:
	UESpriterFileAttributeWrapper(FXmlAttribute2 *attr);

	std::string getName() override;

	bool isValid() override;

	real getRealValue() override;
	int getIntValue() override;
	std::string getStringValue() override;

	void advanceToNextAttribute() override;

private:
	FXmlAttribute2 *attr;
};
