// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "Units/BaseUnit.h"
#include "Units/UnitAIController.h"
#include "Units/StatsComponent.h"

UBTTask_Attack::UBTTask_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Attack";
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::InProgress;
	UnitController = Cast<AUnitAIController>(OwnerComp.GetOwner());
	if (UnitController)
	{
		Pawn = Cast<ABaseUnit>(UnitController->GetPawn());

	}
	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("Attack ticked"));
	if (IsTargetAlive())
	{
		// Do the attack logic here!
		UE_LOG(LogTemp, Warning, TEXT("The unit should be attacking here"));



	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is dead, whaaaat"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

bool UBTTask_Attack::IsTargetAlive()
{
	ABaseUnit* Unit = Cast<ABaseUnit>(Target);
	bool Alive = false;
	if (Unit)
	{
		Alive = Unit->StatsManager->IsUnitAlive();
	}
	return Alive;
}