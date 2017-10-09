// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Interact.h"
#include "Units/UnitAIController.h"
#include "Units/ActionsComponent.h"
#include "Units/BaseUnit.h"
#include "DataStructures.h"
#include "Player/GeneralController.h"


UBTTask_Interact::UBTTask_Interact(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Interact";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Interact::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	AUnitAIController* Controller = Cast<AUnitAIController>(OwnerComp.GetOwner());
	if (Controller)
	{
		FActionInformation Action = Controller->ActionsManager->ActionQueue[0];
		AActor* Enemy = Action.Target;
		if (Enemy)
		{
			Controller->MoveToActor(Enemy, 150.f);
		}

	}



	UE_LOG(LogTemp, Warning, TEXT("The task interact was called, yay!"));

	return NodeResult;
}

void UBTTask_Interact::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AUnitAIController* UnitController = Cast<AUnitAIController>(OwnerComp.GetOwner());
	if (UnitController)
	{
		ABaseUnit* Pawn = Cast<ABaseUnit>(UnitController->GetPawn());
		AActor* Target = UnitController->GetTargetActor();

		if (FVector::Dist(Pawn->GetActorLocation(), Target->GetActorLocation()) < 160.f)
		{
			AGeneralController* PlayerController = Cast<AGeneralController>(GetWorld()->GetFirstPlayerController());
			if (PlayerController)
			{
				PlayerController->InteractableActor = Target;
			}
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}