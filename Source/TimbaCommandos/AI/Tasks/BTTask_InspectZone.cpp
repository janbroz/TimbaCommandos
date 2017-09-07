// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_InspectZone.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationPath.h"

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
	bFinishedPatrol = false;
	MaxPatrolZones = 2;
	CurrentPatrolZones = 0;


	AActor* AIActor = OwnerComp.GetOwner();
	if (AIActor)
	{
		AAIController* AIController = Cast<AAIController>(AIActor);
		if (AIController)
		{
			ControlledPawn = AIController->GetPawn();
			LocationOfCuriosity = ControlledPawn->GetActorLocation();
		}
	}

	// Do something crazy here
	return NodeResult;
}

void UBTTask_InspectZone::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// The AI saw an enemy in this location and is going to investigate.
	// He is already were the enemy was supposed to be but he sees nothing, 
	// he needs to investigate the area around.

	//UE_LOG(LogTemp, Warning, TEXT("My god, the task is ticking"));
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
				UE_LOG(LogTemp, Warning, TEXT("We need to move to a random location"));
				// Do what is left to finish the patrol.
				InspectAdyacentLocation(OwnerComp);
			}
		}
		else
		{
			// Look at the right side.
			if (ControlledPawn)
			{
				LookAtAngle(ControlledPawn, 90.f, DeltaSeconds);
			}
		}
	}
	else
	{
		// Look at the left.
		if (ControlledPawn)
		{
			LookAtAngle(ControlledPawn, -90.f, DeltaSeconds);
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

bool UBTTask_InspectZone::InspectAdyacentLocation(UBehaviorTreeComponent& OwnerComp)
{
	bool ValidInspection = false;
	if (ControlledPawn)
	{
		FVector ActorLocation = LocationOfCuriosity;
		ActorLocation.X += FMath::FRandRange(-1200.f, 1200.f);
		ActorLocation.Y += FMath::FRandRange(-1200.f, 1200.f);
		AAIController* PawnController = Cast<AAIController>(OwnerComp.GetOwner());

		UNavigationPath* NavPath;
		UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
		NavPath = NavSys->FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), ActorLocation);

		// Check if the random is valid.
		if (NavPath != nullptr)
		{
			if (PawnController)
			{
				// Get the navsys and check if the path is traversable, if not re-random the location!
				PawnController->MoveToLocation(ActorLocation, 20.f);
				CurrentPatrolZones++;
				bSearchedLeft = false;
				bSearchedRight = false;
				if (CurrentPatrolZones >= MaxPatrolZones)
				{
					bFinishedPatrol = true;
				}
				ValidInspection = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("My gosh, we cannot get there"));
		}
	}
	return ValidInspection;
}