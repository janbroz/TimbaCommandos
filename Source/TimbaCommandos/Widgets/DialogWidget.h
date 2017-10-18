// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class TIMBACOMMANDOS_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UDialogWidget(const FObjectInitializer& ObjectInitializer);
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Widget functions")
		void InitializeDialog();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Widget functions")
		void ValidateFlowButtons();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget information")
		TArray<FString> DialogOptions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget information")
		UTexture2D* Portrait;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget information")
		int32 DialogIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget information")
		int32 DialogSize;
};
