// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManager.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryManager::UInventoryManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxWeight = 50.f;
	CurrentWeight = 0.f;
}


// Called when the game starts
void UInventoryManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UpdateWeight();
}


// Called every frame
void UInventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<AItem*> UInventoryManager::GetInventory()
{
	return Inventory;
}

bool UInventoryManager::AddItem(AItem* Item)
{
	// TODO, we need some logic to make sure the user can add the item to the inventory.
	bool bSuccess = true;
	Inventory.Add(Item);

	return bSuccess;
}

bool UInventoryManager::RemoveItem(int32 Index)
{
	bool bSuccess = true;
	Inventory.RemoveAt(Index);

	return bSuccess;
}

void UInventoryManager::UpdateWeight()
{
	float UpdatedWeight = 0.f;
	for (auto Item : Inventory)
	{
		UpdatedWeight += Item->Weight;
		Item->AddToInventory();
	}
	CurrentWeight = UpdatedWeight;
}