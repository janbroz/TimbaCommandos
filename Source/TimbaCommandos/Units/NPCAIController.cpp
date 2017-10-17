// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCAIController.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"

ANPCAIController::ANPCAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Tree_BP(TEXT("/Game/Blueprints/Units/AI/BaseNPC/BaseNPC_BT"));
	if (Tree_BP.Object != nullptr)
	{
		BehaviorTree = Tree_BP.Object;
	}
}
