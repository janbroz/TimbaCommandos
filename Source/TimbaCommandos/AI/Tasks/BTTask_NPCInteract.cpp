// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_NPCInteract.h"
#include "Units/UnitAIController.h"
#include "Units/BaseUnit.h"

UBTTask_NPCInteract::UBTTask_NPCInteract(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "NPC Interact";
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_NPCInteract::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::InProgress;


	return Result;
}

void UBTTask_NPCInteract::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AUnitAIController* UnitController = Cast<AUnitAIController>(OwnerComp.GetOwner());
	if (UnitController)
	{
		ABaseUnit* Pawn = Cast<ABaseUnit>(UnitController->GetPawn());
		AActor* Target = UnitController->GetTargetActor();

		float Distance = FVector::Dist(Target->GetActorLocation(), Pawn->GetActorLocation());
		if (Distance >= 200.f && Pawn->GetVelocity().Size() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("I just peed a bit"));
			UnitController->MoveToActor(Target);
		}
		else if (Distance < 200.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("We are close to the guy, lets talk!"));
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}