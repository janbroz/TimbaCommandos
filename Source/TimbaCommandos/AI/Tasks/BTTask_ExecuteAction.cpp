// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ExecuteAction.h"
#include "Units/UnitAIController.h"
#include "Units/ActionsComponent.h"

UBTTask_ExecuteAction::UBTTask_ExecuteAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Execute Action";
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_ExecuteAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Succeeded;

	AActor* AIActor = OwnerComp.GetOwner();
	if (AIActor)
	{
		AUnitAIController* AIController = Cast<AUnitAIController>(AIActor);
		if (AIController)
		{
			if (AIController->ActionsManager && AIController->ActionsManager->ActionQueue.IsValidIndex(0))
			{
				UE_LOG(LogTemp, Warning, TEXT("Unit has an action manager"));
				FActionInformation EvaluatedAction = AIController->ActionsManager->ActionQueue[0];
				EUnitAction Action = EvaluatedAction.Action;

				if (Action == EUnitAction::Move)
				{
					AIController->MoveToLocation(EvaluatedAction.Destiny, 50.f);
					NodeResult = EBTNodeResult::InProgress;
				}

				/*AIController->ActionsManager->ActionQueue.RemoveAt(0);
				AIController->UpdateActionQueue();*/
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Nope"));
			}
			/*FActionInformation* EvaluatedAction = &AIController->ActionsManager->ActionQueue[0];
			EUnitAction Action = EvaluatedAction->Action;
			switch (Action)
			{
			case EUnitAction::Move:
				AIController->MoveToLocation(EvaluatedAction->Destiny);
				break;
			case EUnitAction::Attack:
				break;
			case EUnitAction::Interact:
				break;
			case EUnitAction::None:
				break;
			default:
				break;
			}*/

			//AIController->ActionsManager->ActionQueue.RemoveAt(0);
		}
	}


	return NodeResult;
}


void UBTTask_ExecuteAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("It is ticking"));

	AActor* AIActor = OwnerComp.GetOwner();
	AUnitAIController* AIController = Cast<AUnitAIController>(AIActor);
	if (AIController && AIController->GetMoveStatus() == EPathFollowingStatus::Idle)
	{
		if (AIController->GetIfInterrupted())
		{
			AIController->InterruptActions(false);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Yay, im interrupted"));
			AIController->ActionsManager->ActionQueue.RemoveAt(0);
			AIController->UpdateActionQueue();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}	
	}
}