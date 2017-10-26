// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_NPCInteract.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UBTTask_NPCInteract : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_NPCInteract(const FObjectInitializer& ObjectInitializer);
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
