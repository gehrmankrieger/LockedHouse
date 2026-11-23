#include "Pickups/SupplyPickup.h"
#include "Components/SphereComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/StaticMeshComponent.h"

ASupplyPickup::ASupplyPickup()
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

void ASupplyPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASupplyPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASupplyPickup::Interact_Implementation(AActor* Interactor)
{
	if (!IsValid(Interactor))
	{
		return;
	}

	UInventoryComponent* SupplyComponent = Interactor->FindComponentByClass<UInventoryComponent>();
	if (!SupplyComponent)
	{
		return;
	}

	IsSupplied = SupplyComponent->AddSupply(SupplyTag, Amount);

	if (IsSupplied)
	{
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s not added to supplies."), *SupplyTag.ToString());
	}
}

