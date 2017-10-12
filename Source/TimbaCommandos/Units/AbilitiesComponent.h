// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitiesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMBACOMMANDOS_API UAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilitiesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Use ability at slot
	virtual void UseAbilityAtSlot(int32 Index);

	// Use ability
	virtual void UseAbility(class AAbility* Ability);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		FString AbilityName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability variables")
		TArray<class AAbility*> Abilities;
	
};
