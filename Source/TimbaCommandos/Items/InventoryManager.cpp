// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManager.h"
#include "Item.h"
#include "Engine/World.h"
#include "Player/GeneralController.h"
#include "Units/PlayerUnit.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

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

	if (Item && FreeSlots > 0)
	{
		FItemInformation ItemToAdd;
		if (Item->bIsQuestItem)
		{
			ItemToAdd = FItemInformation(Item->Name, Item->Description, Item->Weight, Item->GetClass(), Item->Icon, ESlotState::Used, true, Item->QuestTarget, Item->UsableDistance);
		}
		else
		{
			ItemToAdd = FItemInformation(Item->Name, Item->Description, Item->Weight, Item->GetClass(), Item->Icon, ESlotState::Used);
		}
		int32 IndexToAdd = GetFirstEmptySlot();
		Inventory[IndexToAdd] = ItemToAdd;
		UpdatePlayerHUDInventory();
		Item->bInInventory = true;
		Item->Destroy();
		FreeSlots--;	
	}
	else
	{
		bSuccess = false;
	}
	return bSuccess;
}

bool UInventoryManager::RemoveItem(int32 Index)
{
	bool bSuccess = true;
	FItemInformation EmptySlot = FItemInformation();
	Inventory[Index] = EmptySlot;

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

bool UInventoryManager::TransferItem(int32 IndexFrom, int32 IndexTo, TScriptInterface<IHasStorageActor> const & FromUnit)
{
	// Aditionally, it needs to check the distance between the actors.
	// and it needs to be a bool!

	bool bTransferSuccessful = false;

	AActor* StorageActor = Cast<AActor>(FromUnit.GetObject());
	float DistanceBetweenActors = GetOwner()->GetDistanceTo(StorageActor);
	IHasStorageActor* TheInterface = Cast<IHasStorageActor>(StorageActor);

	if (TheInterface && DistanceBetweenActors < TRANSFER_DISTANCE)
	{
		//UE_LOG(LogTemp, Warning, TEXT("This should be doing something"));
		//UE_LOG(LogTemp, Warning, TEXT("From is: %s"), *StorageActor->GetName());
		//TheInterface->Execute_GetInventoryManager(StorageActor);
		//FromUnit->Execute_GetInventoryManager();

		
		int32 FromSize = GetSize(TheInterface->Execute_GetInventoryManager(StorageActor)->Inventory[IndexFrom].State);
		int32 ToSize = GetSize(Inventory[IndexTo].State);

		//UE_LOG(LogTemp, Warning, TEXT("From is: %d"), FromSize);
		//UE_LOG(LogTemp, Warning, TEXT("To is: %d"), ToSize);

		FItemInformation TmpItem = Inventory[IndexTo];
		Inventory[IndexTo] = TheInterface->Execute_GetInventoryManager(StorageActor)->Inventory[IndexFrom];
		TheInterface->Execute_GetInventoryManager(StorageActor)->Inventory[IndexFrom] = TmpItem;

		TheInterface->Execute_GetInventoryManager(StorageActor)->FreeSlots += FromSize;
		TheInterface->Execute_GetInventoryManager(StorageActor)->FreeSlots -= ToSize;
		FreeSlots += ToSize;
		FreeSlots -= FromSize;

		UpdatePlayerHUDInventory();

		bTransferSuccessful = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Something fucked up here"));
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

void UInventoryManager::UseItemFromSlot(int32 Index)
{
	FItemInformation ItemToUse = Inventory[Index];
	
	// Make sure the slot has a valid item
	if (ItemToUse.State == ESlotState::Used)
	{
		//AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(ItemToUse.ItemClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), FActorSpawnParameters());
		AItem* SpawnedItem = GetWorld()->SpawnActorDeferred<AItem>(ItemToUse.ItemClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
		if (SpawnedItem)
		{
			
			
			if (ItemToUse.bIsQuestItem)
			{
				SpawnedItem->bIsQuestItem = ItemToUse.bIsQuestItem;
				SpawnedItem->UsableDistance = ItemToUse.UsableDistance;
				SpawnedItem->QuestTarget = ItemToUse.QuestTarget;
			}
			UGameplayStatics::FinishSpawningActor(SpawnedItem, FTransform(SpawnedItem->GetActorRotation(), SpawnedItem->GetActorLocation()));
		}
		

		if (SpawnedItem)
		{
			bool bSuccessfulUse = SpawnedItem->UseItem(GetOwner());
			if (bSuccessfulUse)
			{
				if (ItemToUse.bIsStackable)
				{
					ItemToUse.Amount--;
					if (ItemToUse.Amount <= 0)
					{
						RemoveItem(Index);
					}
				}
				else
				{
					RemoveItem(Index);
				}
			}
		}
		UpdatePlayerHUDInventory();
	}
}