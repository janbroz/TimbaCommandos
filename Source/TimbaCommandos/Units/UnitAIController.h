// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API AUnitAIController : public AAIController
{
	GENERATED_BODY()
public:
	AUnitAIController(const FObjectInitializer& ObjectInitializer);
	
	// Tick override
	virtual void Tick(float DeltaSeconds) override;

	// Our sensing function
	UFUNCTION()
		void SenseVision(TArray<AActor*> SensedActors);

	UFUNCTION()
		virtual void DebugSeeingActors();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit variables")
		class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit variables")
		TArray<AActor*> SensedActors;

};
