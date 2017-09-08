// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemInformation
{
	GENERATED_BODY()
public:
	FItemInformation(FName NewName, FString NewDescription)
	{
		Name = NewName;
		Description = NewDescription;
	}
	FItemInformation() {}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item information")
		FName Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item information")
		FString Description;
};


class TIMBACOMMANDOS_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
