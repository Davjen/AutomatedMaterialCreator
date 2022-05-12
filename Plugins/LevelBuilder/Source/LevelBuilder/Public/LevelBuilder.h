// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FLevelBuilderModule : public IModuleInterface, public FSelfRegisteringExec
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	typedef AActor* (FLevelBuilderModule::*CreateObj)(const int32 X, const int32 Y, UWorld* InWorld);

	void LevelInitFromTxT(const FString& Path);
	void LevelInitFromPng(const FString& Path);
	virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;


	AActor* CreateWall(const int32 X, const int32 Y, UWorld* InWorld);
	AActor* CreateDamageableWall(const int32 X, const int32 Y, UWorld* InWorld);

	TMap<FString,CreateObj> MapCreatorFunctions;

};

