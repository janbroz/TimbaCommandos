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

	// Pawn possesing
	virtual void Possess(class APawn* InPawn) override;

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
	// Our behavior tree stuff.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit AI")
		class UBehaviorTree* BehaviorTree;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit AI")
		UBlackboardComponent* BlackboardComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit AI")
		class UBehaviorTreeComponent* BehaviorTreeComponent;


};
