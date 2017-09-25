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
	
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//InitializeStats();
	UpdatePercents();
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
	UE_LOG(LogTemp, Warning, TEXT("They called me"));

	for (auto Stat = Stats.CreateIterator(); Stat; ++Stat)
	{
		Stat.Value().Percent = Stat.Value().CurrentValue / Stat.Value().MaxValue;
	}
}

float UStatsComponent::GetHealthPercent() const
{
	float Percent = Stats.Find(EStat::Health)->Percent;
	return Percent;
}

float UStatsComponent::GetStatPercent(EStat Stat) const
{
	float Percent = Stats.Find(Stat)->Percent;
	return Percent;
}

void UStatsComponent::UpdateStatMax(EStat Stat, float Value)
{
	FStatInformation* Info = Stats.Find(Stat);
	Info->MaxValue = Value;
	UpdateStatPercent(Stat);
}

void UStatsComponent::UpdateStatMin(EStat Stat, float Value)
{
	FStatInformation* Info = Stats.Find(Stat);
	Info->MinValue = Value;
}

void UStatsComponent::UpdateStatCurrent(EStat Stat, float Value)
{
	FStatInformation* Info = Stats.Find(Stat);
	Info->CurrentValue = Value;
	UpdateStatPercent(Stat);
}

void UStatsComponent::UpdateStatPercent(EStat Stat)
{
	FStatInformation* Info = Stats.Find(Stat);
	Info->Percent = Info->CurrentValue / Info->MaxValue;
}