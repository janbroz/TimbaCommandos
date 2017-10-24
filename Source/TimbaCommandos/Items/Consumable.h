// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Consumable.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API AConsumable : public AItem
{
	GENERATED_BODY()
public:
	AConsumable();
	// We already defined the UseItem(Target) at our parent class, lets change its implementation
	// to reflect that we are using a consumable!
	bool UseItem_Implementation(AActor* Target);
	
	// Some information to have in mind about the consumable:
public:




};
