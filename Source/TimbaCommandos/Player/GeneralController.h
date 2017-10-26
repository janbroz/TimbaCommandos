// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DataStructures.h"
#include "GeneralController.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API AGeneralController : public APlayerController
{
	GENERATED_BODY()
public:
	AGeneralController();
	
	// Setup the player inputs:
	virtual void SetupInputComponent() override;
	

	// Left mouse pressed
	void LeftMousePressed();
	// If we are going to use rectangle selection
	void ReleaseLeftMouse();

	// Right mouse pressed
	void RightMousePressed();

	// Vertical movement
	void VerticalMov(float Amount);

	// Horizontal movement
	void HorizontalMov(float Amount);

	// Rotate camera
	void RotateCamera(float Amount);

	// Toggle control modifier
	void ToggleControl();

	// Reset control. Unit modifier was bugging/
	void ResetControl();

	// User finished drawing a rectangle.
	void GenerateSelectingRectangle();

	// Tick it
	virtual void Tick(float DeltaSeconds) override;

	// Begin play override
	virtual void BeginPlay() override;

	// Update the dragging stuff
	void RectangleDrag();

	// Void clear selected units
	void UpdateSelectedUnitsDecal(bool bSelected);

	// Initialize our HUD with the controllable units
	void InitializeControlledUnits();

	// If we have a unit selected open the inventory
	void ToggleInventory();

	// Update the inventory widget!
	UFUNCTION(BlueprintCallable, Category = "HUD stuff")
		void UpdateInventoryWidgets();

	// Make the player queue actions
	void ToggleQueue();

	// Dialog with the NPCs
	//void BeginDialog(TArray<FDialogInformation> Dialog, UTexture2D* Portrait);
	void BeginDialog(class ANPCUnit* Npc);

	// TODO - Player should be able to bind abilities to different keys.
	// Cast The first ability.
	UFUNCTION(BlueprintCallable, Category = "Ability cast")
		void Ability1Pressed();
	// Cast The second ability.
	UFUNCTION(BlueprintCallable, Category = "Ability cast")
		void Ability2Pressed();
	// Cast The third ability.
	UFUNCTION(BlueprintCallable, Category = "Ability cast")
		void Ability3Pressed();
	// Cast The forth ability.
	UFUNCTION(BlueprintCallable, Category = "Ability cast")
		void Ability4Pressed();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		uint32 bPressingCtrl : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		uint32 bDraggingMouse : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		uint32 bShowingInventory : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		uint32 bQueueActions : 1;
	// Player can select either one or multiple units
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		TArray<class APlayerUnit*> SelectedUnits;
	// The units that the player can use on this level.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		TArray<class APlayerUnit*> AvailableUnits;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		FVector2D Init;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		FVector2D End;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		class UHUDWidget* MainHUD;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		TSubclassOf<class UHUDWidget> MainHUDClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		AActor* InteractableActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		class UDialogWidget* CurrentDialogWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player variables")
		TSubclassOf<UDialogWidget> CurrentDialogClass;
};
