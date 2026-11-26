// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "GameFramework/Controller.h"
#include "LockedHouseCharacter.h"
#include "LockedHouseCollision.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponComponent::Fire()
{
	ALockedHouseCharacter* LockedHouseCharacter = Cast<ALockedHouseCharacter>(GetOwner());
	if (!IsValid(LockedHouseCharacter))
	{
		return;
	}

	LockedHouseCharacter->GetController()->GetPlayerViewPoint(Where, Facing);
	FVector Start = Where;
	FVector End = Start + Facing.Vector() * WeaponRange;

	FHitResult Hit;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, WeaponCollision::WeaponChannel);

	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3.f);
	}

	if (!bHit)
	{
		return;
	}
}

void UWeaponComponent::Reload()
{
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

