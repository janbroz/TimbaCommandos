// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ManageActions.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UBTTask_ManageActions : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_ManageActions(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
