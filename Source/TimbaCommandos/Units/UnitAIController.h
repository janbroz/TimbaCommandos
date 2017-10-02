// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DataStructures.h"
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

	UFUNCTION(BlueprintCallable)
		void UpdateActionQueue();

	UFUNCTION(BlueprintCallable)
		void InterruptActions(bool Interrupt);

	UFUNCTION(BlueprintCallable)
		bool GetIfInterrupted();

	UFUNCTION(BlueprintCallable)
		void StopCurrentTask();

	UFUNCTION(BlueprintCallable)
		void GetCurrentTaskState();

	UFUNCTION(BlueprintCallable)
		void AddActionToQueue(FActionInformation ActionInfo, bool Stack);

	UFUNCTION(BlueprintCallable)
		bool IsUnitActive();

	UFUNCTION(BlueprintCallable)
		void ChangeCurrentAction(EUnitAction Action);

	UFUNCTION(BlueprintCallable)
		void UpdateTargetActor(AActor* NewTarget);
	UFUNCTION(BlueprintCallable)
		void UpdateTargetLocation(FVector NewLocation);
	UFUNCTION(BlueprintCallable)
		AActor* GetTargetActor();
	UFUNCTION(BlueprintCallable)
		void Attack(AActor* Target);
	UFUNCTION(BlueprintCallable)
		void ResetAttackCooldown();


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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit variables")
		class UActionsComponent* ActionsManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit variables")
		uint32 bCanAttack : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit variables")
		float AttackCooldown;
	
	FTimerHandle CooldownTimer;


};
