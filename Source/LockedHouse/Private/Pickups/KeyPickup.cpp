#include "Pickups/KeyPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InventoryComponent.h"

AKeyPickup::AKeyPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionObjectType(ECC_Visibility);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Sphere->SetGenerateOverlapEvents(false);
	Sphere->SetSphereRadius(60.f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AKeyPickup::OnPickedUp_Implementation(AActor* Collector)
{
	
}

void AKeyPickup::Interact_Implementation(AActor* Interactor)
{
	if (!IsValid(Interactor))
	{
		return;
	}

	UInventoryComponent* InventoryComponent = Interactor->FindComponentByClass<UInventoryComponent>();
	if (!InventoryComponent)
	{
		return;
	}

	if (!InventoryComponent->HasPickedUp(KeyTag)) {
		IsPickedUp = InventoryComponent->PickUp(KeyTag);
		
		if (IsPickedUp)
		{
			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Warning: %s"), *GetActorNameOrLabel());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is already picked up."), *KeyTag.ToString());
	}
}