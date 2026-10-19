#include "Pickups/HealthPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HealthComponent.h"

AHealthPickup::AHealthPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(60.f);
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Sphere->SetGenerateOverlapEvents(true);
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::HandleCollision);
	
}

void AHealthPickup::HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || OtherActor == this || OtherComponent != OtherActor->GetRootComponent())
	{
		return;
	}

	UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
	if (!HealthComponent || HealthComponent->IsFull() || HealthComponent->IsDead())
	{
		return;
	}

	const float HealthBefore = HealthComponent->GetHealth();
	HealthComponent->Heal(HealAmount);
	--UsesLeft;

	UE_LOG(LogTemp, Log, TEXT("%s healed %s: %.1f -> %.1f (%d uses left)"),
	*GetName(), *OtherActor->GetName(), HealthBefore, HealthComponent->GetHealth(), UsesLeft);

	OnPickedUp(OtherActor);

	if (UsesLeft <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s used up, destroying"), *GetName());
		Destroy();
	}
}

void AHealthPickup::OnPickedUp_Implementation(AActor* Collector)
{
	UE_LOG(LogTemp, Log, TEXT("%s picked up by %s"), *GetName(), *GetNameSafe(Collector));
}

