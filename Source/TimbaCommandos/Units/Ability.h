// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

UCLASS()
class TIMBACOMMANDOS_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Use the ability
	UFUNCTION(BlueprintCallable, Category = "Ability functions")
		void UseAbility();

	void ResetCooldown();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		USceneComponent* AbilityTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		class USphereComponent* CollisionSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		uint32 bIsPassive : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		uint32 bCanBeUsed : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		float TickInterval;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		float BaseCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		float CurrentCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		float AbilityRadious;

	FTimerHandle CooldownHandler;

};
