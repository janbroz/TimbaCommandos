// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Attack(const FObjectInitializer& ObjectInitializer);
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	bool IsTargetAlive();


public:
	AActor* Target;
	class ABaseUnit* Pawn;
	class AUnitAIController* UnitController;
};
