// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"
#include "Classes/Kismet/KismetSystemLibrary.h"
#include "Units/BaseUnit.h"


AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2100.f;


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
			}
		}
	}
}