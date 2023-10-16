// Copyright Epic Games, Inc. All Rights Reserved.

#include "Duarr.h"
//#define WIN32_LEAN_AND_MEAN

#include "Windows/WindowsWindow.h"
#include <playsoundapi.h>
#include "Windows.h"

#include "Misc/Paths.h"
#include "Misc/CoreDelegates.h"
#define LOCTEXT_NAMESPACE "FDuarrModule"

void FDuarrModule::HandleSystemError()
{
	// TODO: Create picker for sound file, for now just play ahh.wav in Resources
	// Check if file exists
	if (!FPaths::FileExists(ResourceDir))
	{
		UE_LOG(LogTemp, Error, TEXT("File not found: %s"), *ResourceDir);
		return;
	}

	const LPCWSTR Path = *ResourceDir;
	
	// TODO: Have workaround for non-windows platforms
	PlaySound(Path, nullptr, SND_FILENAME |/* SND_ASYNC |*/ SND_NODEFAULT | SND_NOWAIT | SND_SYSTEM | SND_NOSTOP);
}

void FDuarrModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	ResourceDir = FPaths::ProjectPluginsDir() / TEXT("Duarr/Resources/ahh.wav");

	UE_LOG(LogTemp, Warning, TEXT("File found: %s"), *ResourceDir);
	
	FCoreDelegates::OnHandleSystemError.AddRaw(this, &FDuarrModule::HandleSystemError);
}

void FDuarrModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDuarrModule, Duarr)