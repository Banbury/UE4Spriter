#include "SpriterPluginPrivatePCH.h"
#include "UESpriterFileDocumentWrapper.h"
#include "UESpriterFileElementWrapper.h"
#include "SpriterProject.h"

UESpriterFileDocumentWrapper::UESpriterFileDocumentWrapper() : SpriterFileDocumentWrapper()
{
	xmlFile = NULL;
}

UESpriterFileDocumentWrapper::~UESpriterFileDocumentWrapper()
{
	if (xmlFile != NULL)
	{
		delete xmlFile;
	}
}

void UESpriterFileDocumentWrapper::loadFile(std::string fileName)
{
	if (xmlFile != NULL)
	{
		delete xmlFile;
	}
	
	USpriterProject *project = Cast<USpriterProject>(StaticLoadObject(USpriterProject::StaticClass(), NULL, ANSI_TO_TCHAR(fileName.c_str())));

	xmlFile = new FXmlFile(project->Content, EConstructMethod::ConstructFromBuffer);
}

SpriterFileElementWrapper *UESpriterFileDocumentWrapper::newElementWrapperFromFirstElement()
{
	return new UESpriterFileElementWrapper(xmlFile->GetRootNode());
}

SpriterFileElementWrapper *UESpriterFileDocumentWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
{
	return new UESpriterFileElementWrapper(xmlFile->GetRootNode());
}
