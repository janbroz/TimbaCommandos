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
		virtual void UseAbility();

	// Reset the cd
	UFUNCTION(BlueprintCallable, Category = "Ability functions")
		virtual void ResetCooldown();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability functions")
		void ApplyEffect() const;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		USceneComponent* AbilityTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		class USphereComponent* CollisionSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability variables")
		uint32 bIsPassive : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability variables")
		uint32 bCanBeUsed : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability variables")
		float TickInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability variables")
		float BaseCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability variables")
		float CurrentCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability variables")
		float AbilityRadious;

	FTimerHandle CooldownHandler;
	FTimerHandle TickHandler;

};
