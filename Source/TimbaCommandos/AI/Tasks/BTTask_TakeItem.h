// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TakeItem.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UBTTask_TakeItem : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_TakeItem(const FObjectInitializer& ObjectInitializer);
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

public:
	AActor* ItemTarget;
	class ABaseUnit* Pawn;
	class AUnitAIController* UnitController;
};
