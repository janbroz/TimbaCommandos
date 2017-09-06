// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "InspectZone_Task.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UInspectZone_Task : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UInspectZone_Task(const FObjectInitializer& ObjectInitializer);
	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual  EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
