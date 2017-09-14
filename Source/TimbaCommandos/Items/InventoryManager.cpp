// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManager.h"
#include "Item.h"
#include "Engine/World.h"
#include "Player/GeneralController.h"
#include "Units/PlayerUnit.h"

// Sets default values for this component's properties
UInventoryManager::UInventoryManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxWeight = 50.f;
	MaxSlots = 9;
	FreeSlots = 9;
	UsedSlots = 0;
	CurrentWeight = 0.f;
	
}


// Called when the game starts
void UInventoryManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UpdateWeight();
	InitializeInventory();
}


// Called every frame
void UInventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryManager::InitializeInventory()
{
	for (auto i = 0; i < MaxSlots; ++i)
	{
		FItemInformation EmptySlot = FItemInformation();
		Inventory.Add(EmptySlot);
	}
}

TArray<FItemInformation> UInventoryManager::GetInventory()
{
	return Inventory;
}

bool UInventoryManager::AddItem(AItem* Item)
{
	// TODO, we need some logic to make sure the user can add the item to the inventory.
	bool bSuccess = true;

	if (FreeSlots > 0)
	{
		FItemInformation ItemToAdd = FItemInformation(Item->Name, Item->Description, Item->Weight, Item->StaticClass(), Item->Icon, ESlotState::Used);
		int32 IndexToAdd = GetFirstEmptySlot();
		Inventory[IndexToAdd] = ItemToAdd;
		UpdatePlayerHUDInventory();
		Item->Destroy();
		FreeSlots--;
		return bSuccess;
	}
	else
	{
		bSuccess = false;
		return bSuccess;
	}
}

bool UInventoryManager::RemoveItem(int32 Index)
{
	bool bSuccess = true;
	Inventory.RemoveAt(Index);

	return bSuccess;
}

bool UInventoryManager::MoveItem(int32 IndexFrom, int32 IndexTo)
{
	return true;
}

void UInventoryManager::UpdateWeight()
{
	float UpdatedWeight = 0.f;
	for (auto Item : Inventory)
	{
		UpdatedWeight += Item.Weight;
	}
	CurrentWeight = UpdatedWeight;
}

bool UInventoryManager::HasEmptySlot()
{
	// This might be redundant, cause we already have a freeSlot variable.

	bool bHasSlot = false;

	for(auto Slot : Inventory)
	{
		if (Slot.State == ESlotState::Empty)
		{
			bHasSlot = true;
			return bHasSlot;
		}
	}
	return bHasSlot;
}

int32 UInventoryManager::GetFirstEmptySlot()
{
	int32 EmptySlot = 0;
	for (auto i = 0; i < MaxSlots; ++i)
	{
		if (Inventory[i].State == ESlotState::Empty)
		{
			EmptySlot = i;
			break;
		}
	}
	return EmptySlot;
}

void UInventoryManager::UpdatePlayerHUDInventory()
{
	AGeneralController* Pc = Cast<AGeneralController>(GetWorld()->GetFirstPlayerController());
	// We need also to check if the player is showing the inventory and the unit is selected
	if (Pc)
	{
		Pc->UpdateInventoryWidgets();
	}
}

void UInventoryManager::SwapItem(int32 IndexFrom, int32 IndexTo)
{
	FItemInformation TmpItem = Inventory[IndexTo];
	Inventory[IndexTo] = Inventory[IndexFrom];
	Inventory[IndexFrom] = TmpItem;
	UpdatePlayerHUDInventory();
}

bool UInventoryManager::TransferItem(int32 IndexFrom, int32 IndexTo, APlayerUnit* FromUnit)
{
	// Aditionally, it needs to check the distance between the actors.
	// and it needs to be a bool!

	bool bTransferSuccessful = false;

	float DistanceBetweenActors = GetOwner()->GetDistanceTo(FromUnit);

	if (DistanceBetweenActors < TRANSFER_DISTANCE)
	{
		int32 FromSize = GetSize(FromUnit->InventoryManager->Inventory[IndexFrom].State);
		int32 ToSize = GetSize(Inventory[IndexTo].State);

		UE_LOG(LogTemp, Warning, TEXT("From is: %d"), FromSize);
		UE_LOG(LogTemp, Warning, TEXT("To is: %d"), ToSize);

		FItemInformation TmpItem = Inventory[IndexTo];
		Inventory[IndexTo] = FromUnit->InventoryManager->Inventory[IndexFrom];
		FromUnit->InventoryManager->Inventory[IndexFrom] = TmpItem;

		FromUnit->InventoryManager->FreeSlots += FromSize;
		FromUnit->InventoryManager->FreeSlots -= ToSize;
		FreeSlots += ToSize;
		FreeSlots -= FromSize;

		UpdatePlayerHUDInventory();

		bTransferSuccessful = true;
	}
	return bTransferSuccessful;
}

int32 UInventoryManager::GetSize(ESlotState State)
{
	// If the slot is empty the value is 0, else 1.
	switch (State)
	{
	case ESlotState::Empty:
		return 0;
		break;
	case ESlotState::Used:
		return 1;
		break;
	default:
		return 1;
		break;
	}
}