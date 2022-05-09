// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMaterialCreatorrModule : public IModuleInterface,public FSelfRegisteringExec
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void ModifyTexture(const TArray<FAssetData> Data);
	static void CreateMaterial(const FString& Path);
	static TArray<UObject*> ImportAsset(const TArray<FString>& Files);
	bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

};
