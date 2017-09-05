// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"
#include "Classes/Kismet/KismetSystemLibrary.h"
#include "Units/BaseUnit.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2100.f;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Tree_BP(TEXT("/Game/Blueprints/Units/AI/BaseEnemy/BaseEnemy_BT"));
	if (Tree_BP.Object != nullptr)
	{
		BehaviorTree = Tree_BP.Object;
	}
}

void AEnemyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	// Here is what we need to do.
	
}

void AEnemyAIController::DebugSeeingActors()
{
	if (SensedActors.Num() > 0)
	{
		for (auto Actor : SensedActors)
		{
			ABaseUnit* Unit = Cast<ABaseUnit>(Actor);
			if (Unit)
			{
				UKismetSystemLibrary::DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), Actor->GetActorLocation(), FColor::Red, 0.03f, 2.f);
				BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), Unit);
			}
		}
	}
	AActor* CurrentTarget = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("TargetActor")));
	if (CurrentTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("We havea target"));
		if (!SensedActors.Contains(CurrentTarget))
		{
			UE_LOG(LogTemp, Warning, TEXT("He is out of our reach!"));
			BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), nullptr);
			BlackboardComponent->SetValueAsBool(TEXT("bSawEnemy"), true);
			BlackboardComponent->SetValueAsVector(TEXT("EnemyLastSeenAt"), CurrentTarget->GetActorLocation());
			StopMovement();
		}
	}

}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();


}