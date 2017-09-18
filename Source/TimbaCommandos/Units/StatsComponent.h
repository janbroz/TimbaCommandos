// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataStructures.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMBACOMMANDOS_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	void InitializeStats();
	void UpdatePercents();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TMap<EStat, FStatInformation> Stats;
	
};
