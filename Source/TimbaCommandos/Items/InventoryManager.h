// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataStructures.h"
#include "Items/HasStorageActor.h"
#include "InventoryManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMBACOMMANDOS_API UInventoryManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	const float TRANSFER_DISTANCE = 300.f;
	void SetupItemInformation(AItem* Item, const FItemInformation ItemInfo);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Return the inventory
	UFUNCTION(BlueprintCallable)
		TArray<FItemInformation> GetInventory();
	UFUNCTION(BlueprintCallable)
		bool AddItem(class AItem* Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(int32 Index);
	UFUNCTION(BlueprintCallable)
		bool MoveItem(int32 IndexFrom, int32 IndexTo);
	// If we need to make sure that the weight is correct at the beginning of the game.
	UFUNCTION(BlueprintCallable)
		void UpdateWeight();
	UFUNCTION(BlueprintCallable)
		void InitializeInventory();
	UFUNCTION(BlueprintCallable)
		bool HasEmptySlot();
	UFUNCTION(BlueprintCallable)
		int32 GetFirstEmptySlot();
	UFUNCTION(BlueprintCallable)
		void UpdatePlayerHUDInventory();
	UFUNCTION(BlueprintCallable)
		void SwapItem(int32 IndexFrom, int32 IndexTo);
	UFUNCTION(BlueprintCallable)
		bool TransferItem(int32 IndexFrom, int32 IndexTo, TScriptInterface<IHasStorageActor> const & FromUnit);
	UFUNCTION(BlueprintCallable)
		void UseItemFromSlot(int32 Index);
	UFUNCTION(BlueprintCallable)
		void DropItem(int32 Index);

	int32 GetSize(ESlotState Slot);

public:
	// The players inventory
	UPROPERTY(Category = InventoryInformation, BlueprintReadWrite, EditAnywhere)
		TArray<FItemInformation> Inventory;
	
	// Inventory slots
	UPROPERTY(Category = InventoryInformation, BlueprintReadWrite, EditAnywhere)
		int32 MaxSlots;
	UPROPERTY(Category = InventoryInformation, BlueprintReadWrite, EditAnywhere)
		int32 UsedSlots;
	UPROPERTY(Category = InventoryInformation, BlueprintReadWrite, EditAnywhere)
		int32 FreeSlots;

	// Player max weight allowed
	UPROPERTY(Category= InventoryInformation, BlueprintReadWrite, EditAnywhere)
		float MaxWeight;

	// Player current weight
	UPROPERTY(Category = InventoryInformation, BlueprintReadWrite, VisibleAnywhere)
		float CurrentWeight;

};
