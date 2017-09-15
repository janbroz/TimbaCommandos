// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class EUnitClass : uint8
{
	Warrior				UMETA(DisplayName = "Warrior"),
	Wizard				UMETA(DisplayName = "Wizard"),
	Thief				UMETA(DisplayName = "Thief"),
	Archer				UMETA(DisplayName = "Archer")
};

UENUM(BlueprintType)
enum class ESlotState : uint8
{
	Empty				UMETA(DisplayName = "Empty"),
	Used				UMETA(DisplayName = "Used")
};

inline uint8 GetTypeHash(const EUnitClass A) { return (uint8)A; }
inline uint8 GetTypeHash(const ESlotState A) { return (uint8)A; }

USTRUCT(BlueprintType)
struct FItemInformation
{
	GENERATED_BODY()
public:

	

	FItemInformation(FName NewName, FString NewDescription, float NewWeight, TSubclassOf<class AItem> NewClass, UTexture2D* NewIcon, ESlotState NewState)
	{
		Name = NewName;
		Description = NewDescription;
		Weight = NewWeight;
		ItemClass = NewClass;
		Icon = NewIcon;
		State = NewState;
	}
	FItemInformation() { State = ESlotState::Empty; ItemClass = nullptr; Icon = nullptr; }

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		ESlotState State;
};



class TIMBACOMMANDOS_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
