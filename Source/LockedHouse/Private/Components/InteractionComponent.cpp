#include "Components/InteractionComponent.h"
#include "Interfaces/Interactable.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UInteractionComponent::TryInteract()
{
	AActor* Target = FindInteractable();
	if (!Target)
	{
		return;
	}

	IInteractable::Execute_Interact(Target, GetOwner());
}

AActor* UInteractionComponent::FindInteractable() const
{
	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return nullptr;
	}

	const AController* Controller = OwnerPawn->GetController();
	if (!Controller)
	{
		return nullptr;
	}

	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const float CameraToPawn = FVector::Dist(ViewLocation, OwnerPawn->GetActorLocation());
	const FVector Start = ViewLocation;
	const FVector End = Start + ViewRotation.Vector() * (CameraToPawn + InteractRange);

	FHitResult Hit;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);

	if (bDrawDebug)
	{
		const FVector LineEnd = bHit ? FVector(Hit.ImpactPoint) : End;
		DrawDebugLine(GetWorld(), Start, LineEnd, bHit ? FColor::Green : FColor::Red, false, 3.f);

	}

	if (!bHit)
	{
		return nullptr;
	}

	AActor* HitActor = Hit.GetActor();
	if (!IsValid(HitActor) || !HitActor->Implements<UInteractable>() || !IInteractable::Execute_CanInteract(HitActor, GetOwner()))
	{
		return nullptr;
	}

	if (FVector::Dist(OwnerPawn->GetActorLocation(), Hit.ImpactPoint) > InteractRange)
	{
		return nullptr;
	}

	return HitActor;

}