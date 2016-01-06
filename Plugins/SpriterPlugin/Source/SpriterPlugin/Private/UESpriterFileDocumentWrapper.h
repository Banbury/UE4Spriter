#pragma once

#include "override/spriterfiledocumentwrapper.h"
#include "XmlFile.h"

using namespace SpriterEngine;

class UESpriterFileDocumentWrapper : public SpriterFileDocumentWrapper
{
public:
	UESpriterFileDocumentWrapper();
	~UESpriterFileDocumentWrapper() override;

	void loadFile(std::string fileName) override;

private:
	SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
	SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

	FXmlFile *xmlFile;
};
