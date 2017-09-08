// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataStructures.h"
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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Return the inventory
	UFUNCTION(BlueprintCallable)
		TArray<class AItem*> GetInventory();
	UFUNCTION(BlueprintCallable)
		bool AddItem(class AItem* Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(int32 Index);
	// If we need to make sure that the weight is correct at the beginning of the game.
	UFUNCTION(BlueprintCallable)
		void UpdateWeight();


public:
	// The players inventory
	UPROPERTY(Category=InventoryInformation, BlueprintReadWrite, EditAnywhere)
		TArray<class AItem*> Inventory;
	UPROPERTY(Category = InventoryInformation, BlueprintReadWrite, EditAnywhere)
		TArray<FItemInformation> NewInventory;
	
	// Player max weight allowed
	UPROPERTY(Category= InventoryInformation, BlueprintReadWrite, EditAnywhere)
		float MaxWeight;

	// Player current weight
	UPROPERTY(Category = InventoryInformation, BlueprintReadWrite, VisibleAnywhere)
		float CurrentWeight;

};
