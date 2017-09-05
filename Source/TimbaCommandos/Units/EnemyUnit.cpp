// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyUnit.h"
#include "EnemyAIController.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

AEnemyUnit::AEnemyUnit()
{


	AIControllerClass = AEnemyAIController::StaticClass();
	
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}
