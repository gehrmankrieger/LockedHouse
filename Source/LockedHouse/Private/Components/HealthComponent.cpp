

#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();	

	Health = MaxHealth;

	Damage(10);

}

void UHealthComponent::Damage(float Amount)
{
	if (Amount < 0.f)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage amount: %f"), Amount)
	ApplyHealthChange(-Amount);
}

void UHealthComponent::Heal(float Amount)
{
	if (Amount <= 0.f)
	{
		return;
	}

	ApplyHealthChange(Amount);
}


void UHealthComponent::ApplyHealthChange(float Delta)
{
	const float PrevHealth = Health;
	Health = FMath::Clamp((Health + Delta), DEAD, MaxHealth);

	if (PrevHealth == Health)
	{
		return;
	}

	OnHealthChanged.Broadcast(Health, MaxHealth);

	if (Health <= DEAD)
	{
		OnDeath.Broadcast();
	}

}