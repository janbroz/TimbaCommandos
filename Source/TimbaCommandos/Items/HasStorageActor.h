// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "HasStorageActor.generated.h"


class UInventoryManager;
// This class does not need to be modified.
UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UHasStorageActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TIMBACOMMANDOS_API IHasStorageActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintCallable, Category = "Storage interface implementation")
	UFUNCTION(BlueprintCallable, Category = "Storage interface implementation")
		virtual UInventoryManager* GetInventoryManager() const = 0;
	
};
