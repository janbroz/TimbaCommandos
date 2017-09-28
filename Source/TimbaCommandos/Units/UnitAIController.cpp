// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"
#include "Classes/Kismet/KismetSystemLibrary.h"
#include "Units/BaseUnit.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Units/ActionsComponent.h"

AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	// Unit perception, perceptive play!
	SetPerceptionComponent(*ObjectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("Perception")));
	//PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Unit perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight component"));
	
	SightConfig->SightRadius = 800.f;
	SightConfig->LoseSightRadius = 1000.f;
	SightConfig->PeripheralVisionAngleDegrees = 60.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetAIPerceptionComponent()->ConfigureSense(*SightConfig);
	GetAIPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());
	GetAIPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AUnitAIController::SenseVision);

	// Register as a stimuli
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());

	// Unit AI
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("UnitAIComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("UnitBehaviorTree"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Tree_BP(TEXT("/Game/Blueprints/Units/AI/BaseUnit/BaseUnit_BT"));
	if (Tree_BP.Object != nullptr)
	{
		BehaviorTree = Tree_BP.Object;
	}

	// Action queue
	ActionsManager = CreateDefaultSubobject<UActionsComponent>(TEXT("ActionsManager"));
}

void AUnitAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	DebugSeeingActors();
}

void AUnitAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	// Do something crazy here.
	if (BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*BehaviorTree, EBTExecutionMode::Looped);
		BlackboardComponent->SetValueAsVector(TEXT("SpawnLocation"), InPawn->GetActorLocation());
		BlackboardComponent->SetValueAsRotator(TEXT("SpawnRotation"), InPawn->GetActorRotation());
	}
}

void AUnitAIController::SenseVision(TArray<AActor*> SensingActors)
{
	//UE_LOG(LogTemp, Warning, TEXT("Houston, we saw an actor"));
	
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
				//BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), Unit);
			}
		}
	}	
}

void AUnitAIController::UpdateActionQueue()
{
	if (ActionsManager->ActionQueue.Num() > 0)
	{
		if (BehaviorTree)
		{
			UE_LOG(LogTemp, Warning, TEXT("Updated action manager yay"));
			BlackboardComponent->SetValueAsBool(TEXT("bHasPendingActions"), true);
		}
	}
	else
	{
		if (BehaviorTree)
		{
			UE_LOG(LogTemp, Warning, TEXT("Updated action manager nay"));
			BlackboardComponent->SetValueAsBool(TEXT("bHasPendingActions"), false);
		}
	}
}

void AUnitAIController::InterruptActions(bool Interrupt)
{
	if (BehaviorTree)
	{
		BlackboardComponent->SetValueAsBool(TEXT("bInterruptedAction"), Interrupt);
	}
}

bool AUnitAIController::GetIfInterrupted()
{
	bool Interrupted = BlackboardComponent->GetValueAsBool(TEXT("bInterruptedAction"));
	return Interrupted;
}

void AUnitAIController::StopCurrentTask()
{
	
	InterruptActions(true);
}

void AUnitAIController::GetCurrentTaskState()
{
	if (BehaviorTree)
	{
		FString text = BehaviorTreeComponent->DescribeActiveTasks();
		
		UE_LOG(LogTemp, Warning, TEXT("The task description is: %d"), BehaviorTreeComponent->GetActiveInstanceIdx());
		//BehaviorTreeComponent->DescribeActiveTasks();
	}
}

void AUnitAIController::AddActionToQueue(FActionInformation ActionInfo, bool Stack)
{
	if (Stack)
	{
		ActionsManager->ActionQueue.Add(ActionInfo);
	}
	else
	{
		TArray<FActionInformation> TmpArray;
		TmpArray.Add(ActionInfo);
		ActionsManager->ActionQueue = TmpArray;
	}
	UpdateActionQueue();
}

bool AUnitAIController::IsUnitActive()
{
	bool Active = (uint8)EUnitAction::None != BlackboardComponent->GetValueAsEnum(TEXT("CurrentAction"));


	return Active;
}