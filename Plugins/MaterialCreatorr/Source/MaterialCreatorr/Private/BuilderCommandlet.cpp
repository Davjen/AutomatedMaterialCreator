// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderCommandlet.h"
//#include "HAL/FileManager.h"
#include "MaterialCreatorr.h"
#include "Commandlets/Commandlet.h"

int32 UBuilderCommandlet::Main(const FString& Path)
{
    UE_LOG(LogTemp, Warning, TEXT("This is the path chosen %s"), *Path);

    TArray<FString>Commands;
    Path.ParseIntoArray(Commands, TEXT(","));
    //UE_LOG(LogTemp, Warning, TEXT("This is data %s"), *Commands);
    
    if (Commands[0].Contains(FString("BuildMaterial")))
    {
        UE_LOG(LogTemp, Warning, TEXT("This is the path parsed %s"), *Commands[1]);
        FString PathToUse = Commands[1];
        FMaterialCreatorrModule::CreateMaterial(*PathToUse);
    }
    //if (Path.Compare(FString("BuildMaterial")))
    //{

    //    FString Pippo=FCommandLine::GetOriginalForLogging();
    //    UE_LOG(LogTemp, Warning, TEXT("This is data %s"),*Pippo);
    //}
    return 0;
}


