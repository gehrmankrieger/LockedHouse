// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LockedHouseAnimInstance.generated.h"

class ALockedHouseCharacter;

/**
 * 
 */
UCLASS()
class LOCKEDHOUSE_API ULockedHouseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	float Direction = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float AimPitch = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	bool bShouldMove = false;
	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	bool bIsAiming = false;

private:

	UPROPERTY()
	TObjectPtr<ALockedHouseCharacter> OwnerCharacter;
};
