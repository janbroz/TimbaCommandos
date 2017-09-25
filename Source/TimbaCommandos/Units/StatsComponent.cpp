// Fill out your copyright notice in the Description page of Project Settings.

#include "StatsComponent.h"


// Sets default values for this component's properties
UStatsComponent::UStatsComponent(const FObjectInitializer& ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	InitializeStats();
	UpdatePercents();
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//InitializeStats();
	//UpdatePercents();
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::InitializeComponent()
{
	Super::InitializeComponent();

	
}

void UStatsComponent::InitializeStats()
{
	FStatInformation Health = FStatInformation(TEXT("Health"));
	Stats.Add(EStat::Health, Health);

	FStatInformation Mana = FStatInformation(TEXT("Mana"));
	Stats.Add(EStat::Mana, Mana);

	FStatInformation Strength = FStatInformation(TEXT("Strength"));
	Stats.Add(EStat::Strength, Strength);

	FStatInformation Agility = FStatInformation(TEXT("Agility"));
	Stats.Add(EStat::Agility, Agility);

	FStatInformation Stamina = FStatInformation(TEXT("Stamina"));
	Stats.Add(EStat::Stamina, Stamina);

	FStatInformation Intellect = FStatInformation(TEXT("Intellect"));
	Stats.Add(EStat::Intellect, Intellect);
}

void UStatsComponent::UpdatePercents()
{
	for (auto Stat : Stats)
	{
		FString Texty = Stat.Value.Name.ToString();

		UE_LOG(LogTemp, Warning, TEXT("Stat name is: %s"), *Texty);
		UE_LOG(LogTemp, Warning, TEXT("Max value is: %f"), Stat.Value.CurrentValue);

		Stat.Value.Percent = Stat.Value.MaxValue / Stat.Value.CurrentValue;
	}
}

void UStatsComponent::ApplyDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	FStatInformation* ModifiedStat = Stats.Find(EStat::Health);
	UE_LOG(LogTemp, Warning, TEXT("Stat value is: %f"), ModifiedStat->CurrentValue);
	UE_LOG(LogTemp, Warning, TEXT("Damage to the unit is: %f"), DamageAmount);
	ModifiedStat->CurrentValue = FMath::Clamp(ModifiedStat->CurrentValue - DamageAmount, ModifiedStat->MinValue, ModifiedStat->MaxValue);

	if (ModifiedStat->CurrentValue <= ModifiedStat->MinValue)
	{
		ReportUnitDying();
	}

	FDamageEvent FDE;
	
}

void UStatsComponent::ReportUnitDying()
{
	UE_LOG(LogTemp, Warning, TEXT("Unit is kaput!"));
}