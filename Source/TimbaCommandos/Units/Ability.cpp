// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Components/SphereComponent.h"
#include "Units/BaseUnit.h"
#include "Units/StatsComponent.h"

// Sets default values
AAbility::AAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	AbilityTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Ability Transform"));
	RootComponent = AbilityTransform;
	bCanBeUsed = true;
	BaseCooldown = 2.f;
	CurrentCooldown = BaseCooldown;

	AbilityRadious = 256.f;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision sphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->InitSphereRadius(AbilityRadious);
	//CollisionSphere->bHiddenInGame = false;

}

// Called when the game starts or when spawned
void AAbility::BeginPlay()
{
	Super::BeginPlay();
	
	if (bIsPassive && TickInterval > 0.f)
	{
		GetWorldTimerManager().SetTimer(TickHandler, this, &AAbility::ApplyEffect, TickInterval, true);
	}

}

// Called every frame
void AAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (bIsPassive)
	{
		UseAbility();
	}*/

}

void AAbility::UseAbility()
{
	if (bCanBeUsed && !bIsPassive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Holi, me usaron!"));
		bCanBeUsed = false;
		GetWorldTimerManager().SetTimer(CooldownHandler, this, &AAbility::ResetCooldown, CurrentCooldown, false, CurrentCooldown);
		CollisionSphere->bHiddenInGame = !CollisionSphere->bHiddenInGame;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Holi, estoy en cooldown!"));
	}

}

void AAbility::ResetCooldown()
{
	bCanBeUsed = true;
}

void AAbility::ApplyEffect_Implementation() const
{
	UE_LOG(LogTemp, Warning, TEXT("Passive ticked! from: %s"), GetOwner());
	ABaseUnit* Instigator = Cast<ABaseUnit>(GetOwner());
	if (Instigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("Instigator is valid!"));
		Instigator->StatsManager->UpdateStatCurrent(EStat::Health, 1.f);
	}
}