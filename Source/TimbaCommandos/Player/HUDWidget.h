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
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void ShowInventory(const TArray<TScriptInterface<IHasStorageActor>> & Units, bool bShowing);
		//void ShowInventory(const TArray<class APlayerUnit*>& Unit, bool bShowing);
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void ShowDialogBox(class UDialogWidget* DialogWidget);
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void CloseDialogBox();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD information")
		uint32 bShowingInventroy : 1;

};
