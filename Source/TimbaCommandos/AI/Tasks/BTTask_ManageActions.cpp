// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ManageActions.h"
#include "Units/UnitAIController.h"



UBTTask_ManageActions::UBTTask_ManageActions(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Manage actions";
}

EBTNodeResult::Type UBTTask_ManageActions::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Succeeded;
	AUnitAIController* UnitController = Cast<AUnitAIController>(OwnerComp.GetOwner());
	if (UnitController)
	{
		UnitController->ChangeCurrentAction(EUnitAction::None);
		UnitController->UpdateTargetActor(nullptr);
		UnitController->UpdateTargetLocation(FVector::ZeroVector);
	}
	return Result;
}