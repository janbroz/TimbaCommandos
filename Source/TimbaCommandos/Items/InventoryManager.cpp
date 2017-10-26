// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManager.h"
#include "Item.h"
#include "Engine/World.h"
#include "Player/GeneralController.h"
#include "Units/PlayerUnit.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

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
	if (!Item)return false;

	// Check if the player can carry the new item
	float NewWeight = CurrentWeight + Item->Weight;
	if (NewWeight <= MaxWeight)
	{
		// We can add the item to a new stack
		bool bSuccessfulyStacked = false;
		if (Item->bCanBeStacked)
		{
			for (FItemInformation& ItemInfo : Inventory)
			{
				if (ItemInfo.ItemClass == Item->GetClass())
				{
					ItemInfo.Amount++;
					bSuccessfulyStacked = true;
					break;
				}
			}
			// It means the item can be stacked but there is not a stack to add it to.
			if (!bSuccessfulyStacked)
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
				ItemToAdd.bIsStackable = Item->bCanBeStacked;
				int32 IndexToAdd = GetFirstEmptySlot();
				Inventory[IndexToAdd] = ItemToAdd;
				FreeSlots--;
				UsedSlots++;
				UpdatePlayerHUDInventory();
			}
		}
		else
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
			FreeSlots--;
			UsedSlots++;
			UpdatePlayerHUDInventory();
		}
		Item->bInInventory = true;
		Item->Destroy();
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
	FItemInformation& CurrentSlot = Inventory[Index];
	if (CurrentSlot.Amount > 1)
	{
		CurrentSlot.Amount--;
	}
	else
	{
		FItemInformation EmptySlot = FItemInformation();
		Inventory[Index] = EmptySlot;
		FreeSlots++;
		UsedSlots--;
	}
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
		int32 FromSize = GetSize(TheInterface->Execute_GetInventoryManager(StorageActor)->Inventory[IndexFrom].State);
		int32 ToSize = GetSize(Inventory[IndexTo].State);

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
	// This should call the use item. If it is a consumable consume it, if it is an equipable equip it!
	FItemInformation& ItemToUse = Inventory[Index];
	if (ItemToUse.State == ESlotState::Used)
	{
		//AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(ItemToUse.ItemClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), FActorSpawnParameters());
		FTransform Transf = FTransform(GetOwner()->GetActorRotation(), GetOwner()->GetActorLocation());
		const AActor* Owner = GetOwner();
		const APawn* Instigator = Cast<APawn>(Owner);
		AItem* SpawnedItem = GetWorld()->SpawnActorDeferred<AItem>(ItemToUse.ItemClass, Transf, GetOwner(), Cast<APawn>(GetOwner()), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
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
			SpawnedItem->SetActorEnableCollision(false);
			SpawnedItem->ItemMesh->SetSimulatePhysics(false);
			SpawnedItem->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
			bool bSuccessfulUse = SpawnedItem->UseItem(GetOwner());
			if (bSuccessfulUse)
			{
				if (ItemToUse.bIsStackable)
				{
					UE_LOG(LogTemp, Warning, TEXT("Item is stackable and should be modified"));
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
			SpawnedItem->Destroy();
		}
		UpdatePlayerHUDInventory();
	}
}

void UInventoryManager::DropItem(int32 Index)
{
	FItemInformation ItemToUse = Inventory[Index];
	FTransform Transf = FTransform(GetOwner()->GetActorRotation(), GetOwner()->GetActorLocation());
	const AActor* Owner = GetOwner();
	const APawn* Instigator = Cast<APawn>(Owner);
	AItem* SpawnedItem = GetWorld()->SpawnActorDeferred<AItem>(ItemToUse.ItemClass, Transf, GetOwner(), Cast<APawn>(GetOwner()), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (SpawnedItem)
	{
		SpawnedItem->Name = ItemToUse.Name;
		SpawnedItem->Description = ItemToUse.Description;
		SpawnedItem->Weight = ItemToUse.Weight;
		SpawnedItem->bInInventory = false;
		SpawnedItem->bCanBeStacked = ItemToUse.bIsStackable;

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
		SpawnedItem->ItemMesh->IgnoreActorWhenMoving(GetOwner(), true);
		FVector ForwardImpulse = Owner->GetActorForwardVector() * 500.f + Owner->GetActorUpVector() * 1000.f;
		SpawnedItem->ItemMesh->AddImpulse(ForwardImpulse);
		RemoveItem(Index);
	}
	UpdatePlayerHUDInventory();
}

void UInventoryManager::SetupItemInformation(AItem* Item, const FItemInformation ItemInfo)
{
	if (Item)
	{
		Item->Name = ItemInfo.Name;
		Item->Description = ItemInfo.Description;
		Item->Weight = ItemInfo.Weight;
		//Item->Cost = ItemInfo.Cost;
		Item->bCanBeStacked = ItemInfo.bIsStackable;
		Item->bIsQuestItem = ItemInfo.bIsQuestItem;
		Item->UsableDistance = ItemInfo.UsableDistance;
		Item->QuestTarget = ItemInfo.QuestTarget;
	}
}
