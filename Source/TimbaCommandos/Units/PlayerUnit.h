// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/BaseUnit.h"
#include "DataStructures.h"
#include "PlayerUnit.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API APlayerUnit : public ABaseUnit
{
	GENERATED_BODY()

public:
	APlayerUnit();
	

public:
	// This is the class of our unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit information")
		EUnitClass ClassType;
	
};
