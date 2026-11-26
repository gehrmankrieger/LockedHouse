#include "Pickups/HealthPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HealthComponent.h"
#include "LockedHouseCollision.h"

AHealthPickup::AHealthPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionObjectType(ECC_WorldDynamic);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Sphere->SetCollisionResponseToChannel(WeaponCollision::WeaponChannel, ECR_Ignore);
	Sphere->SetGenerateOverlapEvents(false);
	Sphere->SetSphereRadius(60.f);
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AHealthPickup::OnPickedUp_Implementation(AActor* Collector)
{
	UE_LOG(LogTemp, Log, TEXT("%s picked up by %s"), *GetName(), *GetNameSafe(Collector));
}

void AHealthPickup::Interact_Implementation(AActor* Interactor)
{
	if (!IsValid(Interactor))
	{
		return;
	}

	UHealthComponent* HealthComponent = FindUHealthComponent(Interactor);
	if (!HealthComponent || HealthComponent->IsFull() || HealthComponent->IsDead())
	{
		return;
	}
	else
	{

	}

	if (!CanInteract(Interactor))
	{
		return;
	}


	HealthComponent->Heal(HealAmount);
	--UsesLeft;

	OnPickedUp(Interactor);

	UE_LOG(LogTemp, Log, TEXT("current health: %f"), HealthComponent->GetHealth());


	if (UsesLeft <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s used up, destroying"), *GetName());
		Destroy();
	}
}

bool AHealthPickup::CanInteract_Implementation(AActor* Interactor)
{
	UHealthComponent* Health = FindUHealthComponent(Interactor);
	if(!IsValid(Health))
	{
		return false;
	}

	if(Health->IsFull())
	{
		return false;
	}

	return true;
}

UHealthComponent* AHealthPickup::FindUHealthComponent(AActor* Who) const
{
	return Who->FindComponentByClass<UHealthComponent>();
}
