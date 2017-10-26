// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitiesComponent.h"
#include "Units/Ability.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UAbilitiesComponent::UAbilitiesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// First create the abilities that the user defined for the unit.
	for (auto AbilityClass : AbilityClasses)
	{
		AAbility* AbilityFromClass = GetWorld()->SpawnActor<AAbility>(AbilityClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), FActorSpawnParameters());
		if (AbilityFromClass)
		{
			Abilities.Add(AbilityFromClass);
			AbilityFromClass->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
			AbilityFromClass->SetOwner(GetOwner());
		}
		
		
	}

	AAbility* NewAbility =  GetWorld()->SpawnActor<AAbility>(GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(),FActorSpawnParameters());
	Abilities.Add(NewAbility);
	NewAbility->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	NewAbility->SetOwner(GetOwner());
}


// Called every frame
void UAbilitiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilitiesComponent::UseAbility(AAbility* Ability)
{

}

void UAbilitiesComponent::UseAbilityAtSlot(int32 Index)
{
	bool ValidIndex = Abilities.IsValidIndex(Index);
	if (ValidIndex)
	{
		Abilities[Index]->UseAbility();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unit has not abilities in that slot"));
	}

}
