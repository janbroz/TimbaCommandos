// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FinishAction.h"
#include "Units/UnitAIController.h"


EBTNodeResult::Type UBTTask_FinishAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Succeeded;
	AUnitAIController* UnitController = Cast<AUnitAIController>(OwnerComp.GetOwner());

	if (UnitController)
	{
		UnitController->ChangeCurrentAction(EUnitAction::None);
		UnitController->StopCurrentTask();
		UnitController->UpdateActionQueue();
	}

	return Result;
}
