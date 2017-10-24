// Fill out your copyright notice in the Description page of Project Settings.

#include "Consumable.h"



AConsumable::AConsumable()
{

}

void AConsumable::UseItem_Implementation(AActor* Target)
{
	Super::UseItem_Implementation(Target);

	UE_LOG(LogTemp, Warning, TEXT("And also it was consumed!"));
}