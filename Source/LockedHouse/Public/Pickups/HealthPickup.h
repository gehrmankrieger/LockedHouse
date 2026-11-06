// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "HealthPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class LOCKEDHOUSE_API AHealthPickup : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AHealthPickup();

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void OnPickedUp(AActor* Collector);

protected:

	virtual void OnPickedUp_Implementation(AActor* Collector);

	virtual void Interact_Implementation(AActor* Collector) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (ClampMin = "1"));
	float HealAmount = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (ClampMin = "1"));
	int32 UsesLeft = 3;

};
