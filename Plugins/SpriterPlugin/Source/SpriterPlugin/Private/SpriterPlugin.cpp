// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpriterPluginPrivatePCH.h"

#define LOCTEXT_NAMESPACE "FSpriterPluginModule"

void FSpriterPluginModule::StartupModule()
{
}

void FSpriterPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpriterPluginModule, SpriterPlugin)