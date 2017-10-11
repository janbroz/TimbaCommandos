// Fill out your copyright notice in the Description page of Project Settings.

#include "Container.h"
#include "Items/InventoryManager.h"

// Sets default values
AContainer::AContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	InventoryManager = CreateDefaultSubobject<UInventoryManager>(TEXT("Inventory Manager"));
}

// Called when the game starts or when spawned
void AContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UInventoryManager* AContainer::GetInventoryManager_Implementation() const
{
	return InventoryManager;
}

UTexture2D* AContainer::GetPortrait_Implementation() const
{
	return UnitPortrait;
}