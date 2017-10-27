// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestData.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UQuestData : public UObject
{
	GENERATED_BODY()
	
public:
	UQuestData();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AActor* Owner;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EQuestState State;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class UQuestCondition*> Conditions;

};
