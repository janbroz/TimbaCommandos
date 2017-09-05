// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/UnitAIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API AEnemyAIController : public AUnitAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController(const FObjectInitializer& ObjectInitializer);
	
	// Override the possess stuff.
	virtual void Possess(class APawn* InPawn) override;

	UFUNCTION()
		void DebugSeeingActors() override;

	UFUNCTION()
		virtual void BeginPlay() override;
	



};
