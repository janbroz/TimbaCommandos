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
		Target = UnitController->GetTargetActor();
	}
	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//UE_LOG(LogTemp, Warning, TEXT("Attack ticked"));
	UnitController = Cast<AUnitAIController>(OwnerComp.GetOwner());
	if (UnitController)
	{
		Pawn = Cast<ABaseUnit>(UnitController->GetPawn());
		Target = UnitController->GetTargetActor();
	}
	
	if (IsTargetAlive())
	{
		AlignToTarget();
		if (GetInRange() && UnitController->bCanAttack)
		{
			UnitController->Attack(Target);
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Target is dead, whaaaat"));
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


bool UBTTask_Attack::GetInRange()
{
	const float Dist = FVector::Distance(Pawn->GetActorLocation(), Target->GetActorLocation());
	//UE_LOG(LogTemp, Warning, TEXT("Distance to target is: %f"), Dist);

	if (Dist <= 700.f)
	{
		return true;
	}
	else
	{
		UnitController->MoveToActor(Target, 600.f);
		return false;
	}
}

void UBTTask_Attack::AlignToTarget()
{
	// This does an instantaneus rotation. If we want the unit to have rotation speed
	// into account we should use a lerp.
	FRotator NewRot = (Target->GetActorLocation() - Pawn->GetActorLocation()).Rotation();
	Pawn->SetActorRotation(NewRot);

}