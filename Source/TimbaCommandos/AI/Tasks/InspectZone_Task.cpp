// Fill out your copyright notice in the Description page of Project Settings.

#include "InspectZone_Task.h"




UInspectZone_Task::UInspectZone_Task(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{


}


EBTNodeResult::Type UInspectZone_Task::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Succeeded;
}

void UInspectZone_Task::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);



}