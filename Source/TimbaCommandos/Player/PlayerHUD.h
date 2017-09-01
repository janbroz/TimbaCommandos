// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
	// Tick
	virtual void Tick(float DeltaSeconds) override;
	// Draw hud and stuff
	virtual void DrawHUD() override;


	// Need to start and end drawing the rectangle.
	void StartSelectionRectangle(FVector2D StartLocation, FVector2D EndLocation);
	void UpdateSelectionRectangle(FVector2D StartLocation, FVector2D EndLocation);
	void FinishSelectionRectangle(FVector2D StartLocation, FVector2D EndLocation);
	TArray<class ABaseUnit*> GetSelectionResults();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD information")
		uint32 bDrawSelectionRectangle :1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD information")
		TArray<class ABaseUnit*> SelectedUnits;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD information")
		FVector2D RInit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD information")
		FVector2D REnd;
};
