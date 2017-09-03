// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"
#include "Classes/Kismet/KismetSystemLibrary.h"
#include "Units/BaseUnit.h"

AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	// Unit perception, perceptive play!
	SetPerceptionComponent(*ObjectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("Perception")));
	//PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Unit perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight component"));
	
	SightConfig->SightRadius = 800.f;
	SightConfig->LoseSightRadius = 1000.f;
	SightConfig->PeripheralVisionAngleDegrees = 45.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	

	GetAIPerceptionComponent()->ConfigureSense(*SightConfig);
	GetAIPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());
	GetAIPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AUnitAIController::SenseVision);

	// Register as a stimuli
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());
}

void AUnitAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	DebugSeeingActors();
}

void AUnitAIController::SenseVision(TArray<AActor*> SensingActors)
{
	UE_LOG(LogTemp, Warning, TEXT("Houston, we saw an actor"));
	
	//SensedActors = SensingActors;
	SensedActors.Empty();
	GetAIPerceptionComponent()->GetCurrentlyPerceivedActors(SightConfig->GetSenseImplementation(), SensedActors);
	
}

void AUnitAIController::DebugSeeingActors()
{
	if (SensedActors.Num() > 0)
	{
		for (auto Actor : SensedActors)
		{
			ABaseUnit* Unit = Cast<ABaseUnit>(Actor);
			if (Unit)
			{
				UKismetSystemLibrary::DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), Actor->GetActorLocation(), FColor::Black, 0.03f, 2.f);
			}
		}
	}	
}