// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralController.h"
#include "Player/PlayerPawn.h"
#include "Units/BaseUnit.h"
#include "Units/PlayerUnit.h"
#include "Player/PlayerHUD.h"
#include "AIController.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "UserWidget.h"
#include "Player/HUDWidget.h"
#include "Items/Item.h"
#include "Items/InventoryManager.h"

AGeneralController::AGeneralController()
{
	bShowMouseCursor = true;

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
				UpdateSelectedUnitsDecal(false);
				SelectedUnits = PlayerHUD->GetSelectionResults();
				for (auto Unit : SelectedUnits)
				{
					Unit->SetUnitSelected(true);
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

	InputComponent->BindAxis("HorizontalMovement", this, &AGeneralController::HorizontalMov);
	InputComponent->BindAxis("VerticalMovement", this, &AGeneralController::VerticalMov);
	InputComponent->BindAxis("RotateCamera", this, &AGeneralController::RotateCamera);
}


void AGeneralController::LeftMousePressed()
{
	bDraggingMouse = true;
	
	GetMousePosition(Init.X, Init.Y);
	End = Init;

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

		if (!bPressingCtrl)
		{
			UpdateSelectedUnitsDecal(false);
		}
		if (ValidUnit)
		{
			if (bPressingCtrl)
			{
				SelectedUnits.AddUnique(ValidUnit);
			}
			else
			{
				SelectedUnits.Empty();
				SelectedUnits.AddUnique(ValidUnit);
				
			}
			
			ValidUnit->SetUnitSelected(true);
		}else
		{
			if (!bPressingCtrl)
			{
				SelectedUnits.Empty();
			}		
		}
		

		MainHUD->UpdateSelectedUnits(SelectedUnits);
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("We clicked nothing useful"));
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
			AItem* ValidItem = Cast<AItem>(Hit.GetActor());
			if (ValidItem && FVector::Dist(ValidItem->GetActorLocation(), SelectedUnits[0]->GetActorLocation()) < 250.f)
			{
				UE_LOG(LogTemp, Warning, TEXT("The item is close to us man"));
				SelectedUnits[0]->InventoryManager->AddItem(ValidItem);
				ValidItem->Destroy();
			}

			for (auto Unit : SelectedUnits)
			{
				AAIController* UnitController = Cast<AAIController>(Unit->GetController());
				if (UnitController)
				{
					UnitController->MoveToLocation(Hit.Location);
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