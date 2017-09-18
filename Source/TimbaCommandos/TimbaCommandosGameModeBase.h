// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimbaCommandosGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API ATimbaCommandosGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATimbaCommandosGameModeBase(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	
};
