// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/HasStorageActor.h"
#include "Container.generated.h"

UCLASS()
class TIMBACOMMANDOS_API AContainer : public AActor, public IHasStorageActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interface implementation.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Storage interface implementation")
		UInventoryManager* GetInventoryManager() const;
		virtual UInventoryManager* GetInventoryManager_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Storage interface implementation")
		UTexture2D* GetPortrait() const;
		virtual UTexture2D* GetPortrait_Implementation() const;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit variables")
		class UInventoryManager* InventoryManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit variables")
		UTexture2D* UnitPortrait;
};
