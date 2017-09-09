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
	FItemInformation(FName NewName, FString NewDescription, float NewWeight, TSubclassOf<class AItem> NewClass, UTexture2D* NewIcon)
	{
		Name = NewName;
		Description = NewDescription;
		Weight = NewWeight;
		ItemClass = NewClass;
		Icon = NewIcon;
	}
	FItemInformation() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		FName Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item information")
		FString Description;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item information")
		float Weight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item information")
		float Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		TSubclassOf<class AItem> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		UTexture2D* Icon;
};


class TIMBACOMMANDOS_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
