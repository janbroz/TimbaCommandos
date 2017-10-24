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
	// When spawning an item from an item info struct.
	//AItem()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// We are going to add this item to the inventory, need to make it non responsive to the world.
	void AddToInventory();
	void RemoveFromInventory();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weird stuff")
		bool UseItem(AActor* Target);
	bool UseItem_Implementation(AActor* Target);
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInformation)
		uint32 bCanBeStacked : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		uint32 bIsQuestItem : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		AActor* QuestTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item information")
		float UsableDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ItemInformation)
		UStaticMeshComponent* ItemMesh;
};
