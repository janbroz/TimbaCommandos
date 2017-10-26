// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCUnit.h"
#include "NPCAIController.h"

ANPCUnit::ANPCUnit()
{
	AIControllerClass = ANPCAIController::StaticClass();

	bHasQuest = false;
	bQuestIsCompleted = false;
}

void ANPCUnit::CompleteQuest()
{
	bQuestIsCompleted = true;
}