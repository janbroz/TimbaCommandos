// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseUnit.generated.h"

UCLASS()
class TIMBACOMMANDOS_API ABaseUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetUnitSelected(bool bSelected);

	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit variables")
		UDecalComponent* UnitSelectingDecal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit variables")
		UTexture2D* UnitPortrait;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit variables")
		FString UnitName;
	
};
