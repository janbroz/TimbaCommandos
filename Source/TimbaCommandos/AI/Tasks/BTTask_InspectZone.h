// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_InspectZone.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UBTTask_InspectZone : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void LookAtAngle(AActor* Actor, float Angle, float DeltaSeconds);
	bool InspectAdyacentLocation(UBehaviorTreeComponent& OwnerComp);

	UPROPERTY(Category = Node, EditAnywhere)
		uint32 bFinishedPatrol : 1;
	UPROPERTY(Category = Node, EditAnywhere)
		uint32 bSearchedLeft : 1;
	UPROPERTY(Category = Node, EditAnywhere)
		uint32 bSearchedRight : 1;
	UPROPERTY(Category = Node, EditAnywhere)
		int32 MaxPatrolZones;
	UPROPERTY(Category = Node, EditAnywhere)
		int32 CurrentPatrolZones;
	UPROPERTY(Category = Node, EditAnywhere)
		FVector LocationOfCuriosity;
	UPROPERTY(Category = Node, EditAnywhere)
		APawn* ControlledPawn;
};
