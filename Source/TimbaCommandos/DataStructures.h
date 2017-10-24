// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
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

UENUM(BlueprintType)
enum class EUnitAction : uint8
{
	None				UMETA(DisplayName = "None"),
	Move				UMETA(DisplayName = "Move"),
	Attack				UMETA(DisplayName = "Attack"),
	Interact			UMETA(DisplayName = "Interact"),
	NPC_Interact		UMETA(DisplayName = "NPC interact"),
	Take				UMETA(DisplayName = "Take")
};

inline uint8 GetTypeHash(const EUnitClass A) { return (uint8)A; }
inline uint8 GetTypeHash(const ESlotState A) { return (uint8)A; }
inline uint8 GetTypeHash(const EStat A) { return (uint8)A; }
inline uint8 GetTypeHash(const EUnitAction A) { return (uint8)A; }

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
		QuestTarget = nullptr;
	}
	FItemInformation() { State = ESlotState::Empty; ItemClass = nullptr; Icon = nullptr; Weight = 0.f; }

	FItemInformation(FName NewName, FString NewDescription, float NewWeight, TSubclassOf<class AItem> NewClass, UTexture2D* NewIcon, ESlotState NewState,
		bool bQuestItem, AActor* Target, float DistanceToUse)
	{
		Name = NewName;
		Description = NewDescription;
		Weight = NewWeight;
		ItemClass = NewClass;
		Icon = NewIcon;
		State = NewState;
		bIsQuestItem = bQuestItem;
		QuestTarget = Target;
		UsableDistance = DistanceToUse;
	}

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		bool bIsQuestItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		bool bIsStackable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		AActor* QuestTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		float UsableDistance;
};

USTRUCT(BlueprintType)
struct FStatInformation
{
	GENERATED_BODY()
public:
	FStatInformation(FName StatName) { Name = StatName;  MinValue = 0; MaxValue = 1; CurrentValue = 1; Percent = 1; }
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
struct FActionInformation 
{
	GENERATED_BODY()

public:
	FActionInformation() { Action = EUnitAction::None; Instigator = nullptr; Target = nullptr; Priority = 0; }
	FActionInformation(EUnitAction UAction, AActor* UInstigator, AActor* UTarget, FVector UDestiny, int32 UPriority) 
	{ Action = UAction; Instigator = UInstigator; Target = UTarget; Destiny = UDestiny; Priority = UPriority; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action information")
		EUnitAction Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action information")
		AActor* Instigator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action information")
		AActor* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action information")
		FVector Destiny;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action information")
		int32 Priority;
};

USTRUCT(BlueprintType)
struct FDialogOption
{
	GENERATED_BODY()

public:
	FDialogOption() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog information")
		FString Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog information")
		int32 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog information")
		int32 TargetId;
};
USTRUCT(BlueprintType)
struct FDialogInformation
{
	GENERATED_BODY()

public:
	FDialogInformation() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog information")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog information")
		FString DialogText;
	// This id should be unique, cause we reference it from the FDialogOption
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog information")
		int32 DialogId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog information")
		TArray<FDialogOption> Options;

};


class TIMBACOMMANDOS_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
