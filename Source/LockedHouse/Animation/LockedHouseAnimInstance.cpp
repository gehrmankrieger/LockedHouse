// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/LockedHouseAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"
#include "LockedHouseCharacter.h"

void ULockedHouseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerCharacter = Cast<ALockedHouseCharacter>(TryGetPawnOwner());
}

void ULockedHouseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!IsValid(OwnerCharacter)) return;

	const FVector Velocity = OwnerCharacter->GetVelocity();

	GroundSpeed = Velocity.Size2D();

	bShouldMove = GroundSpeed > 3.f;

	bIsAiming = OwnerCharacter->IsAiming();

	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, OwnerCharacter->GetActorRotation());

	AimPitch = FRotator::NormalizeAxis(OwnerCharacter->GetBaseAimRotation().Pitch - OwnerCharacter->GetActorRotation().Pitch);

}

