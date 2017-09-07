// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_InspectZone.h"
#include "AIController.h"



UBTTask_InspectZone::UBTTask_InspectZone(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Inspect Zone";
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_InspectZone::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	UE_LOG(LogTemp, Warning, TEXT("My god, the task was executed"));
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	bSearchedLeft = false;
	bSearchedRight = false;
	bFinishedPatrol = true;
	
	// Do something crazy here
	return NodeResult;
}

void UBTTask_InspectZone::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (bSearchedLeft)
	{
		if (bSearchedRight)
		{
			if (bFinishedPatrol)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
			else
			{
				// Do what is left to finish the patrol.
			}
		}
		else
		{
			// Look at the right side.
			AActor* AIActor = OwnerComp.GetOwner();
			if (AIActor)
			{
				AAIController* AIController = Cast<AAIController>(AIActor);
				if (AIController)
				{
					LookAtAngle(AIController->GetPawn(), 90.f, DeltaSeconds);
				}
			}
		}
	}
	else
	{
		// Look at the left.
		AActor* AIActor = OwnerComp.GetOwner();
		if (AIActor)
		{
			AAIController* AIController = Cast<AAIController>(AIActor);
			if (AIController)
			{
				LookAtAngle(AIController->GetPawn(), -90.f, DeltaSeconds);
			}
		}	
	}
}

void UBTTask_InspectZone::LookAtAngle(AActor* Actor, float Angle, float DeltaSeconds)
{
	FRotator ActorRotation = Actor->GetActorRotation();
	FRotator DestinyRotation = FRotator(ActorRotation.Pitch, Angle, ActorRotation.Roll);

	FRotator InterpRotation = FMath::RInterpTo(ActorRotation, DestinyRotation, DeltaSeconds, 2.f);
	
	if (Actor)
	{
		Actor->SetActorRotation(InterpRotation);

		if (FMath::Abs(InterpRotation.Yaw - DestinyRotation.Yaw) < 10.f)
		{
			if (bSearchedLeft)
			{
				bSearchedRight = true;
			}
			else
			{
				bSearchedLeft = true;
			}
		}	
	}
}