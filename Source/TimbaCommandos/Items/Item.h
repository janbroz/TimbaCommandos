// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class TIMBACOMMANDOS_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// We are going to add this item to the inventory, need to make it non responsive to the world.
	void AddToInventory();
	void RemoveFromInventory();

public:
	// Item information.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInformation)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInformation)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInformation)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInformation)
		int32 Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInformation)
		float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInformation)
		uint32 bInInventory : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ItemInformation)
		UStaticMeshComponent* ItemMesh;
};
