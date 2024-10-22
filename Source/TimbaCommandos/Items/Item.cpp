// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Item mesh
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item mesh"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionProfileName(TEXT("ItemActor"));
	ItemMesh->SetSimulatePhysics(true);
	
	UpdateMassScale(2.f);

	Name = "Basic item";
	Description = "Oh look, its a basic item!";
	Cost = 10;
	Weight = 1;
	bInInventory = false;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// We dont want our objects to weight more than a few pounds!
void AItem::UpdateMassScale(float Value)
{
	FBodyInstance* BodyInstance = ItemMesh->GetBodyInstance();
	if (!BodyInstance) return;
	
	BodyInstance->MassScale = Value;
	BodyInstance->UpdateMassProperties();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::AddToInventory()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	bInInventory = true;
}

void AItem::RemoveFromInventory()
{

}

bool AItem::UseItem_Implementation(AActor* Target)
{
	UE_LOG(LogTemp, Warning, TEXT("Item was used!"));
	return true;
}
