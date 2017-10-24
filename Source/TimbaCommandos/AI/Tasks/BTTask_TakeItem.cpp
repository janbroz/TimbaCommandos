// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_TakeItem.h"
#include "DataStructures.h"
#include "Units/ActionsComponent.h"
#include "Units/UnitAIController.h"
#include "Units/BaseUnit.h"
#include "Items/InventoryManager.h"
#include "Items/Item.h"

UBTTask_TakeItem::UBTTask_TakeItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Take Item";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_TakeItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::InProgress;
	AActor* Controller = OwnerComp.GetOwner();
	if (Controller)
	{
		AUnitAIController* AIController = Cast<AUnitAIController>(Controller);
		if (AIController)
		{
			UnitController = AIController;
			Pawn = Cast<ABaseUnit>(AIController->GetPawn());
			FActionInformation Action = AIController->ActionsManager->ActionQueue[0];
			ItemTarget = Action.Target;
			AItem* Item = Cast<AItem>(ItemTarget);
			if (Item && !Item->bInInventory)
			{
				AIController->MoveToActor(ItemTarget, 100.f);
			}
			else
			{
				Result = EBTNodeResult::Succeeded;
			}	
		}
	}
	return Result;
}


void UBTTask_TakeItem::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (Pawn && ItemTarget)
	{
		float Distance = FVector::Distance(Pawn->GetActorLocation(), ItemTarget->GetActorLocation());
		if (Distance <= 160.f)
		{
			AItem* Item = Cast<AItem>(ItemTarget);
			if (Item && !Item->bInInventory)
			{
				Pawn->InventoryManager->AddItem(Cast<AItem>(Item));
			}
			
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}