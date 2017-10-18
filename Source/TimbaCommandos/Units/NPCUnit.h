// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/BaseUnit.h"
#include "NPCUnit.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API ANPCUnit : public ABaseUnit
{
	GENERATED_BODY()
public:
	ANPCUnit();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog info")
		TArray<FString> DialogOptions;
	
};
