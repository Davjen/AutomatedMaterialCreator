// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/ResavePackagesCommandlet.h"
#include "BuilderCommandlet.generated.h"

/**
 * 
 */
UCLASS()
class MATERIALCREATORR_API UBuilderCommandlet : public UResavePackagesCommandlet
{
	GENERATED_BODY()
public:
	int32 Main(const FString& Path);

};
