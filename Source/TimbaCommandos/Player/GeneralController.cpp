// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralController.h"
#include "Player/PlayerPawn.h"
#include "Units/BaseUnit.h"
#include "Units/PlayerUnit.h"
#include "Units/EnemyUnit.h"
#include "Player/PlayerHUD.h"
#include "AIController.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "UserWidget.h"
#include "Player/HUDWidget.h"
#include "Items/Item.h"
#include "Items/InventoryManager.h"
#include "Units/UnitAIController.h"
#include "Units/ActionsComponent.h"
#include "Items/HasStorageActor.h"

AGeneralController::AGeneralController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	static ConstructorHelpers::FObjectFinder<UClass> PlayerHUD_BP(TEXT("/Game/UMG/MainHUD.MainHUD_C"));
	if (PlayerHUD_BP.Object)
	{
		MainHUDClass = PlayerHUD_BP.Object;
	}
}

void AGeneralController::BeginPlay()
{
	Super::BeginPlay();

	if (MainHUDClass)
	{
		MainHUD = CreateWidget<UHUDWidget>(this, MainHUDClass);
		if (MainHUD)
		{
			MainHUD->AddToViewport();
		}

	}

}

void AGeneralController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	RectangleDrag();
}

void AGeneralController::RectangleDrag()
{
	if (bDraggingMouse)
	{
		GetMousePosition(End.X, End.Y);
		if (Init != End)
		{
			APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD());
			if (PlayerHUD)
			{
				PlayerHUD->UpdateSelectionRectangle(Init, End);
				
				TArray<APlayerUnit*> RectangleSelectedUnits = PlayerHUD->GetSelectionResults();
				if (RectangleSelectedUnits.Num() > 0)
				{
					UpdateSelectedUnitsDecal(false);
					SelectedUnits = RectangleSelectedUnits;
					for (auto Unit : SelectedUnits)
					{
						Unit->SetUnitSelected(true);
					}
					if (bShowingInventory)
					{
						//TArray<FScriptInterface<IHasStorageActor>> StorageActors;
						TArray<TScriptInterface<IHasStorageActor>> TUnits;
						for (auto Unit : SelectedUnits)
						{
							TScriptInterface<IHasStorageActor> TmpUnit; // = Cast<IHasStorageActor>(Unit);
							TmpUnit.SetObject(Unit);
							TUnits.Add(TmpUnit);
						}
						if (InteractableActor)
						{
							TScriptInterface<IHasStorageActor> TmpUnit;
							TmpUnit.SetObject(InteractableActor);
							TUnits.Add(TmpUnit);
						}
						//TUnits.Add(InteractableActor);
						MainHUD->ShowInventory(TUnits, bShowingInventory);
						//MainHUD->ShowInventory(SelectedUnits, bShowingInventory);
					}
				}
				
				if (MainHUD)
				{
					MainHUD->UpdateSelectedUnits(SelectedUnits);
				}
			}
		}	
	}
}

void AGeneralController::UpdateSelectedUnitsDecal(bool bSelected)
{
	for (auto Unit : SelectedUnits)
	{
		Unit->SetUnitSelected(bSelected);
	}
}

void AGeneralController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouse", IE_Pressed, this, &AGeneralController::LeftMousePressed);
	InputComponent->BindAction("LeftMouse", IE_Released, this, &AGeneralController::ReleaseLeftMouse);
	InputComponent->BindAction("RightMouse", IE_Pressed, this, &AGeneralController::RightMousePressed);
	InputComponent->BindAction("Control", IE_Pressed, this, &AGeneralController::ToggleControl);
	InputComponent->BindAction("Control", IE_Released, this, &AGeneralController::ToggleControl);
	InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AGeneralController::ToggleInventory);
	InputComponent->BindAction("ToggleQueue", IE_Pressed, this, &AGeneralController::ToggleQueue);
	InputComponent->BindAction("ToggleQueue", IE_Released, this, &AGeneralController::ToggleQueue);

	InputComponent->BindAxis("HorizontalMovement", this, &AGeneralController::HorizontalMov);
	InputComponent->BindAxis("VerticalMovement", this, &AGeneralController::VerticalMov);
	InputComponent->BindAxis("RotateCamera", this, &AGeneralController::RotateCamera);
}


void AGeneralController::LeftMousePressed()
{
	bDraggingMouse = true;
	
	GetMousePosition(Init.X, Init.Y);
	End = Init;

	InteractableActor = nullptr;

	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD());
	if (PlayerHUD)
	{
		PlayerHUD->StartSelectionRectangle(Init, End);
	}

	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_PhysicsBody, true, Hit);

	if (Hit.Actor != nullptr)
	{
		APlayerUnit* ValidUnit = Cast<APlayerUnit>(Hit.GetActor());
		AItem* ValidItem = Cast<AItem>(Hit.GetActor());

		if (ValidUnit)
		{
			if (bPressingCtrl)
			{
				SelectedUnits.AddUnique(ValidUnit);
			}
			else
			{
				UpdateSelectedUnitsDecal(false);
				SelectedUnits.Empty();
				SelectedUnits.AddUnique(ValidUnit);
			}
			ValidUnit->SetUnitSelected(true);
		}
		
		MainHUD->UpdateSelectedUnits(SelectedUnits);
		if (bShowingInventory)
		{
			//MainHUD->ShowInventory(SelectedUnits, bShowingInventory);
			TArray<TScriptInterface<IHasStorageActor>> TUnits;
			for (auto Unit : SelectedUnits)
			{
				TScriptInterface<IHasStorageActor> TmpUnit; // = Cast<IHasStorageActor>(Unit);
				TmpUnit.SetObject(Unit);
				TUnits.Add(TmpUnit);
			}
			if (InteractableActor)
			{
				TScriptInterface<IHasStorageActor> TmpUnit;
				TmpUnit.SetObject(InteractableActor);
				TUnits.Add(TmpUnit);
			}
			MainHUD->ShowInventory(TUnits, bShowingInventory);
		}
	}
}

void AGeneralController::ReleaseLeftMouse()
{
	GetMousePosition(End.X, End.Y);
	bDraggingMouse = false;

	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD());
	TArray<AActor*> EnclosedActors;
	if (PlayerHUD)
	{
		PlayerHUD->FinishSelectionRectangle(Init, End);
		if (SelectedUnits.Num() == 0)
		{
			SelectedUnits = PlayerHUD->GetSelectionResults();
			UpdateSelectedUnitsDecal(true);

			// Make it so that the inventory widget disapears.
			bShowingInventory = false;
		}
		if (bPressingCtrl)
		{
			TArray<APlayerUnit*> NewUnits = PlayerHUD->GetSelectionResults();
			for (auto Unit : NewUnits)
			{
				SelectedUnits.AddUnique(Unit);
			}
		}
	}
	//GenerateSelectingRectangle();
}

void AGeneralController::GenerateSelectingRectangle()
{
	FVector WorldLoc, WorldDir;
	DeprojectMousePositionToWorld(WorldLoc, WorldDir);
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD());
	TArray<AActor*> EnclosedActors;
	if (PlayerHUD)
	{		
		PlayerHUD->StartSelectionRectangle(Init, End);
	}
}

void AGeneralController::RightMousePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Right click pressed"));
	if (SelectedUnits.Num() != 0)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, true, Hit);

		
		if (Hit.bBlockingHit)
		{
			// There is a lot of duplicated code. I think it is easier to read this way.
			// Could be refactored later.
			AItem* ValidItem = Cast<AItem>(Hit.GetActor());
			AEnemyUnit* EnemyUnit = Cast<AEnemyUnit>(Hit.GetActor());

			// Check if it is a valid item and then queue the get item action
			APlayerUnit* ResponsibleUnit = SelectedUnits[0];
			AUnitAIController* UnitController = Cast<AUnitAIController>(ResponsibleUnit->GetController());
			IHasStorageActor* StorageActor = Cast<IHasStorageActor>(Hit.GetActor());

			// We should check before if the player is trying to queue an action or replace the current one!
			if (bQueueActions)
			{
				// The clicked actor is an item.
				if (ValidItem)
				{
					FActionInformation ActionInfo(EUnitAction::Take, ResponsibleUnit, ValidItem, Hit.Location, 0);
					UnitController->AddActionToQueue(ActionInfo, true);
				}
				// The clicked actor is an enemy.
				else if (EnemyUnit)
				{
					if (EnemyUnit->IsUnitAlive())
					{
						for (auto Unit : SelectedUnits)
						{
							FActionInformation ActionInfo(EUnitAction::Attack, Unit, EnemyUnit, Hit.Location, 0);
							AUnitAIController* AIController = Cast<AUnitAIController>(Unit->GetController());
							AIController->AddActionToQueue(ActionInfo, true);
						}
					}
					else
					{
						for (auto Unit : SelectedUnits)
						{
							FActionInformation ActionInfo(EUnitAction::Interact, Unit, EnemyUnit, Hit.Location, 0);
							AUnitAIController* AIController = Cast<AUnitAIController>(Unit->GetController());
							AIController->AddActionToQueue(ActionInfo, true);
						}
					}
				}
				// The clicked actor is something else.
				else
				{			
					for (auto Unit : SelectedUnits)
					{
						FActionInformation ActionInfo(EUnitAction::Move, Unit, nullptr, Hit.Location, 0);
						AUnitAIController* AIController = Cast<AUnitAIController>(Unit->GetController());
						AIController->AddActionToQueue(ActionInfo, true);
					}
				}		
			}
			else
			{
				if (ValidItem)
				{
					FActionInformation ActionInfo(EUnitAction::Take, ResponsibleUnit, ValidItem, Hit.Location, 0);
					if (UnitController->IsUnitActive())
					{
						UnitController->InterruptActions(true);
					}
					UnitController->AddActionToQueue(ActionInfo, false);
					UnitController->InterruptActions(false);
				}
				// The clicked actor is an enemy.
				else if (EnemyUnit && EnemyUnit->IsUnitAlive())
				{
					
					for (auto Unit : SelectedUnits)
					{
						FActionInformation ActionInfo(EUnitAction::Attack, Unit, EnemyUnit, Hit.Location, 0);
						AUnitAIController* AIController = Cast<AUnitAIController>(Unit->GetController());
						if (AIController->IsUnitActive())
						{
							AIController->InterruptActions(true);
						}
						AIController->AddActionToQueue(ActionInfo, false);
						AIController->InterruptActions(false);
					}
				}
				// The clicked actor is something else.
				else if (StorageActor)
				{
					for (auto Unit : SelectedUnits)
					{
						FActionInformation ActionInfo(EUnitAction::Interact, Unit, Hit.GetActor(), Hit.Location, 0);
						AUnitAIController* AIController = Cast<AUnitAIController>(Unit->GetController());
						if (AIController->IsUnitActive())
						{
							AIController->InterruptActions(true);
						}
						AIController->AddActionToQueue(ActionInfo, false);
						AIController->InterruptActions(false);
					}
				}
				else
				{
					for (auto Unit : SelectedUnits)
					{
						FActionInformation ActionInfo(EUnitAction::Move, Unit, nullptr, Hit.Location, 0);
						AUnitAIController* AIController = Cast<AUnitAIController>(Unit->GetController());
						AIController->MoveToLocation(Hit.Location, 150.f);
						if (AIController->IsUnitActive())
						{
							AIController->InterruptActions(true);
						}
						AIController->AddActionToQueue(ActionInfo, false);
						AIController->InterruptActions(false);
					}
				}
			}
		}
	}
}

void AGeneralController::VerticalMov(float Amount)
{
	if (Amount != 0)
	{
		APlayerPawn* ThePlayer = Cast<APlayerPawn>(GetPawn());
		if (ThePlayer)
		{
			FVector NewActorLocation = ThePlayer->GetActorLocation();
			NewActorLocation += (GetActorForwardVector() * 25.f * Amount);			
			ThePlayer->SetActorLocation(NewActorLocation);
		}
		//UE_LOG(LogTemp, Warning, TEXT("Value from vertical movement is: %f"), Amount);
	}
	
}

void AGeneralController::HorizontalMov(float Amount)
{
	if (Amount != 0)
	{
		APlayerPawn* ThePlayer = Cast<APlayerPawn>(GetPawn());
		if (ThePlayer)
		{
			FVector NewActorLocation = ThePlayer->GetActorLocation();
			NewActorLocation += (GetActorRightVector() * 25.f * Amount);
			ThePlayer->SetActorLocation(NewActorLocation);
		}

		//UE_LOG(LogTemp, Warning, TEXT("Value from horizontal movement is: %f"), Amount);
	}
	
}

void AGeneralController::RotateCamera(float Amount)
{
	if (Amount != 0)
	{
		FRotator CRotation = GetControlRotation();
		CRotation.Yaw += 1.f * Amount;
		SetControlRotation(CRotation);
	}
}

void AGeneralController::ToggleControl()
{
	bPressingCtrl = !bPressingCtrl;
}

void AGeneralController::ResetControl()
{
	bPressingCtrl = false;
}

void AGeneralController::InitializeControlledUnits()
{
	SelectedUnits.Add(AvailableUnits[0]);

	if (MainHUD)
	{
		for (auto Unit : AvailableUnits)
		{
			MainHUD->SetHeroPortrait(Unit);
		}
		MainHUD->UpdateSelectedUnits(SelectedUnits);
		UpdateSelectedUnitsDecal(true);
	}
}

void AGeneralController::ToggleInventory()
{
	//bShowingInventory = !bShowingInventory;

	if (SelectedUnits.Num() > 0)
	{
		bShowingInventory = !bShowingInventory;
	}
	else
	{
		bShowingInventory = false;
	}

	UpdateInventoryWidgets();
}

void AGeneralController::UpdateInventoryWidgets()
{
	if (MainHUD)
	{
		//MainHUD->ShowInventory(SelectedUnits, bShowingInventory);
		TArray<TScriptInterface<IHasStorageActor>> TUnits;
		for (auto Unit : SelectedUnits)
		{
			TScriptInterface<IHasStorageActor> TmpUnit; // = Cast<IHasStorageActor>(Unit);
			TmpUnit.SetObject(Unit);
			TUnits.Add(TmpUnit);
		}
		if (InteractableActor)
		{
			TScriptInterface<IHasStorageActor> TmpUnit;
			TmpUnit.SetObject(InteractableActor);
			TUnits.Add(TmpUnit);
		}
		
		MainHUD->ShowInventory(TUnits, bShowingInventory);
	}

}

void AGeneralController::ToggleQueue()
{
	bQueueActions = !bQueueActions;
}