// Fill out your copyright notice in the Description page of Project Settings.

#include "TimbaCommandosGameModeBase.h"
#include "Player/PlayerPawn.h"
#include "Player/GeneralController.h"
#include "Player/PlayerHUD.h"

ATimbaCommandosGameModeBase::ATimbaCommandosGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AGeneralController::StaticClass();
	HUDClass = APlayerHUD::StaticClass();
}