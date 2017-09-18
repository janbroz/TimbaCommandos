// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"
#include "Units/BaseUnit.h"
#include "Units/PlayerUnit.h"

void APlayerHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bDrawSelectionRectangle)
	{
		SelectedUnits.Empty();
		GetActorsInSelectionRectangle(RInit, REnd, SelectedUnits, false, false);

		//DrawLine(RInit.X, RInit.Y, REnd.X, REnd.Y, FLinearColor::Black, 2.f);
		DrawLine(RInit.X, RInit.Y, REnd.X, RInit.Y, FLinearColor::Black, 2.f);
		DrawLine(RInit.X, REnd.Y, REnd.X, REnd.Y, FLinearColor::Black, 2.f);
		DrawLine(RInit.X, RInit.Y, RInit.X, REnd.Y, FLinearColor::Black, 2.f);
		DrawLine(REnd.X, RInit.Y, REnd.X, REnd.Y, FLinearColor::Black, 2.f);
	}


	
}

void APlayerHUD::StartSelectionRectangle(FVector2D StartLocation, FVector2D EndLocation)
{
	RInit = StartLocation;
	REnd = EndLocation;
	bDrawSelectionRectangle = true;

}

void APlayerHUD::UpdateSelectionRectangle(FVector2D StartLocation, FVector2D EndLocation)
{
	RInit = StartLocation;
	REnd = EndLocation;
}

void APlayerHUD::FinishSelectionRectangle(FVector2D StartLocation, FVector2D EndLocation)
{
	bDrawSelectionRectangle = false;
}

TArray<APlayerUnit*> APlayerHUD::GetSelectionResults()
{
	return SelectedUnits;
}