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

UENUM(BlueprintType)
enum class EStat : uint8
{
	Health				UMETA(DisplayName = "Health"),
	Mana				UMETA(DisplayName = "Mana"),
	Experience			UMETA(DisplayName = "Experience"),
	Agility				UMETA(DisplayName = "Agility"),
	Strength			UMETA(DisplayName = "Strength"),
	Intellect			UMETA(DisplayName = "Intellect"),
	Stamina				UMETA(DisplayName = "Stamina"),
	None				UMETA(DisplayName = "None")
};

inline uint8 GetTypeHash(const EUnitClass A) { return (uint8)A; }
inline uint8 GetTypeHash(const ESlotState A) { return (uint8)A; }
inline uint8 GetTypeHash(const EStat A) { return (uint8)A; }

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

USTRUCT(BlueprintType)
struct FStatInformation
{
	GENERATED_BODY()
public:
	FStatInformation(FName StatName) { Name = StatName;  MinValue = 1; MaxValue = 1; CurrentValue = 1; Percent = 1; }
	FStatInformation() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat information")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat information")
		float MinValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat information")
		float MaxValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat information")
		float CurrentValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat information")
		float Percent;
};

USTRUCT(BlueprintType)
struct FBoundsDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	UPROPERTY()
		float Multiplier;


};


class TIMBACOMMANDOS_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
