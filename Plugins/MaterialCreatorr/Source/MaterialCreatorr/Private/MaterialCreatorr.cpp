// Copyright Epic Games, Inc. All Rights Reserved.
#include "MaterialCreatorr.h"
#include "AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "AutomatedAssetImportData.h"
#include "Editor/EditorEngine.h"
#include "HAL/FileManagerGeneric.h"
#include "ImageUtils.h"
#include "Misc/Paths.h"
#include "Factories/MaterialFactoryNew.h"
#include "Factories/TextureFactory.h"

#define LOCTEXT_NAMESPACE "FMaterialCreatorrModule"

void FMaterialCreatorrModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMaterialCreatorrModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



void FMaterialCreatorrModule::ModifyTexture(const TArray<FAssetData> Data)
{
	for (const FAssetData& Datum : Data)
	{
		UObject* Object = Datum.GetAsset();
		UTexture2D* Texture = Cast<UTexture2D>(Object);

		if (Texture)
		{
			UE_LOG(LogTemp, Warning, TEXT("Name: %d"), Texture->GetSizeX());
			uint8* MipData = Texture->Source.LockMip(0);
			for (int32 X = 0; X < Texture->GetSizeX() * Texture->GetSizeY() * 4; X += 4)
			{
				//bgra
				MipData[X + 2] = 255;
			}
			Texture->Source.UnlockMip(0);
			Texture->PostEditChange();
			Texture->MarkPackageDirty();
		}
	}
}



void FMaterialCreatorrModule::CreateMaterial(const FString& Path)
{
	TArray<FString>ListOfFiles = TArray<FString>();
	FFileManagerGeneric FileManager = FFileManagerGeneric();
	FileManager.FindFilesRecursive(ListOfFiles, *Path, TEXT("*.png"), true, true);

	UE_LOG(LogTemp, Warning, TEXT("File Trovato: %s"), *ListOfFiles[0]);
	TArray<UObject*> Textures = ImportAsset(ListOfFiles);

	for (UObject* Obj : Textures)
	{
		UMaterialFactoryNew* NewMaterial = NewObject<UMaterialFactoryNew>();
		FString AssetName = Obj->GetName();
		
		UPackage* Package = CreatePackage(*FString::Printf(TEXT("/Game/Material/%s"), *AssetName));
		NewMaterial->FactoryCreateNew(NewMaterial->SupportedClass, Package, *AssetName, EObjectFlags::RF_Standalone | EObjectFlags::RF_Public, nullptr, GWarn);
		FAssetRegistryModule::AssetCreated(NewMaterial);
		UMaterial* Material = Cast<UMaterial>(NewMaterial);
		FString FileName = FPackageName::LongPackageNameToFilename(Package->GetPathName(), FPackageName::GetAssetPackageExtension());
		UPackage::SavePackage(Package, Obj, RF_Public | RF_Standalone, *FileName);

		//notify modify on uobj
		//modify uobject
		//notify end of modify

	}
}

TArray<UObject*> FMaterialCreatorrModule::ImportAsset(const TArray<FString>& Files)
{



	for (FString Path : Files)
	{
		Path = Path.Replace(TEXT("\\"), TEXT("/"));
	}
	
	UAutomatedAssetImportData* NewTexture = NewObject<UAutomatedAssetImportData>();
	NewTexture->bReplaceExisting = true; //Replace old with new
	NewTexture->DestinationPath = TEXT("/Game/Assets/Texture");
	NewTexture->Filenames = Files;
	
	
	


	FAssetToolsModule& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	TArray<UObject*>ImportedAssets = AssetTools.Get().ImportAssetsAutomated(NewTexture);

	for (UObject* Obj : ImportedAssets)
	{
		UPackage* Package = Obj->GetPackage();
		FString FileName = FPackageName::LongPackageNameToFilename(Package->GetPathName(), FPackageName::GetAssetPackageExtension());

		UPackage::SavePackage(Package, Obj, RF_Public | RF_Standalone,*FileName);
		FAssetRegistryModule::AssetCreated(Obj);
	}

	return ImportedAssets;
}

bool FMaterialCreatorrModule::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	if (FParse::Command(&Cmd,TEXT("Import")))
	{
		CreateMaterial(FString("C:\\Users\\lelem\\OneDrive\\Immagini\\CartellaImport"));
		return true;
	}
	return false;
}



#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMaterialCreatorrModule, MaterialCreatorr)