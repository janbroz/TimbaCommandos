// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void UpdateSelectedUnits(const TArray<class APlayerUnit*>& SelectedUnits);
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void SetHeroPortrait(class APlayerUnit* Unit);

};
