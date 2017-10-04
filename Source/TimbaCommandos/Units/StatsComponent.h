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

	UFUNCTION(BlueprintCallable, Category = "HUD")
		float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable, Category = "HUD")
		float GetStatPercent(EStat Stat) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	void InitializeStats();
	void UpdatePercents();

public:
	void ApplyDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	// The manager reports to the pawn that the unit just died, it should do stuff like
	// spawn a ragdoll, stop the components ticks and kill the AIs.
	void ReportUnitDying();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Update Stat values
	void UpdateStatMax(EStat Stat, float Value);
	void UpdateStatMin(EStat Stat, float Value);
	void UpdateStatCurrent(EStat Stat, float Value);
	void UpdateStatPercent(EStat Stat);
	UFUNCTION(BlueprintCallable)
		bool IsUnitAlive();
	UFUNCTION(BlueprintCallable)
		void GainExperience(float Amount);
	UFUNCTION(BlueprintCallable)
		void GainLevel();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TMap<EStat, FStatInformation> Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FStatInformation Experience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FStatInformation Level;

};
