// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseUnit.h"
#include "Units/UnitAIController.h"
#include "Components/DecalComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Items/InventoryManager.h"
#include "Units/StatsComponent.h"
#include "Units/AbilitiesComponent.h"

// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// We want something that tell us when the unit is selected.
	UnitSelectingDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal selection"));
	UnitSelectingDecal->SetupAttachment(RootComponent);
	UnitSelectingDecal->bHiddenInGame = true;
	UnitSelectingDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	UnitSelectingDecal->DecalSize = FVector(64.f, 128.f, 128.f);

	AIControllerClass = AUnitAIController::StaticClass();
	UnitName = TEXT("The unit");
	
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimuli source"));
	bIsPlayerControlled = false;

	// The unit inventory
	InventoryManager = CreateDefaultSubobject<UInventoryManager>(TEXT("Inventory manager"));

	// The stats manager
	StatsManager = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsManager"));

	// Abilities manager
	AbilitiesManager = CreateDefaultSubobject<UAbilitiesComponent>(TEXT("AbilitiesManager"));
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
	//UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Im alive, tralalala: %s"), *GetName());
	
}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseUnit::SetUnitSelected(bool bSelected)
{
	if (bSelected)
	{
		UnitSelectingDecal->SetHiddenInGame(false);
	}
	else
	{
		UnitSelectingDecal->SetHiddenInGame(true);
	}
}

UInventoryManager* ABaseUnit::GetInventoryManager_Implementation() const
{
	return InventoryManager;
}

UTexture2D* ABaseUnit::GetPortrait_Implementation() const
{
	return UnitPortrait;
}

//bool ABaseUnit::ReactToHighNoon_Implementation()
//{
//	return true;
//}

float ABaseUnit::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	StatsManager->ApplyDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("Ouch i took %f damage"), ActualDamage);

	return ActualDamage;
}

void ABaseUnit::SetActorKilled()
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	SetActorTickEnabled(false);
	DetachFromControllerPendingDestroy();
	//PrimaryActorTick.bCanEverTick = false;
}

bool ABaseUnit::IsUnitAlive()
{
	return StatsManager->IsUnitAlive();
}