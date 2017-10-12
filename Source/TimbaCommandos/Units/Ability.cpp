// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"
#include "Runtime/Engine/Public/TimerManager.h"

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
}

// Called when the game starts or when spawned
void AAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPassive)
	{
		UseAbility();
	}

}

void AAbility::UseAbility()
{
	if (bCanBeUsed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Holi, me usaron!"));
		bCanBeUsed = false;
		GetWorldTimerManager().SetTimer(CooldownHandler, this, &AAbility::ResetCooldown, CurrentCooldown, false, CurrentCooldown);
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
