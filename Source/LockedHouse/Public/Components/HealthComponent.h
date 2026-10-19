// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, CurrentHealth, float, CurrentMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKEDHOUSE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	const float DEAD = 0.f;

public:	
	UHealthComponent();

	UPROPERTY(BlueprintAssignable, category="Health")
	FOnDeathSignature OnDeath;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, category="Health")
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, category="Health")
	void Damage(float Amount);

	UFUNCTION(BlueprintCallable, category = "Health")
	void Heal(float Amount);

	UFUNCTION(BlueprintPure, category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintPure, category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(Blueprintpure, category = "Health")
	bool IsFull() const { return Health >= MaxHealth; }

	UFUNCTION(BlueprintPure, category = "Health")
	bool IsDead() const { return Health <= DEAD ; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category="Health")
	float Health = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category="Health", meta = (ClampMin = "1"))
	float MaxHealth = 100.f;

private:
	
	void ApplyHealthChange(float Delta);
	
};
