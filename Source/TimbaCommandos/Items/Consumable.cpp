// Fill out your copyright notice in the Description page of Project Settings.

#include "Consumable.h"



AConsumable::AConsumable()
{

}

bool AConsumable::UseItem_Implementation(AActor* Target)
{
	

	UE_LOG(LogTemp, Warning, TEXT("And also it was consumed!"));
	bool bSuperCall = Super::UseItem_Implementation(Target);
	return bSuperCall;
}