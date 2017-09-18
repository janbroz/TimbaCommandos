// Fill out your copyright notice in the Description page of Project Settings.

#include "TimbaCommandosGameModeBase.h"
#include "Player/PlayerPawn.h"
#include "Player/GeneralController.h"
#include "Player/PlayerHUD.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Units/PlayerUnit.h"

ATimbaCommandosGameModeBase::ATimbaCommandosGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AGeneralController::StaticClass();
	HUDClass = APlayerHUD::StaticClass();
}

void ATimbaCommandosGameModeBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Holi, the game just started"));

	AGeneralController* PlayerController = Cast<AGeneralController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		TArray<APlayerUnit*> PlayerUnits;
		for (TActorIterator<APlayerUnit> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			PlayerController->AvailableUnits.Add(*ActorItr);
		}
		PlayerController->InitializeControlledUnits();
	}
}