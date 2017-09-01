// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"

AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	// Unit perception, perceptive play!
	SetPerceptionComponent(*ObjectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("Perception")));
	//PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Unit perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight component"));
	
	SightConfig->SightRadius = 1800.f;
	SightConfig->LoseSightRadius = 2000.f;
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
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

	//UE_LOG(LogTemp, Warning, TEXT("The AI is working"));

	//MoveToLocation(FVector::ZeroVector);
}

void AUnitAIController::SenseVision(TArray<AActor*> SensingActors)
{
	UE_LOG(LogTemp, Warning, TEXT("Houston, we saw an actor"));
}