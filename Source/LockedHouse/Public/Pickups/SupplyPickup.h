// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "GameplayTagContainer.h"
#include "SupplyPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class LOCKEDHOUSE_API ASupplyPickup : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASupplyPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(AActor* Interactor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Supply")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Supply")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category = "Supply", meta = (Categories = "Item.Supply"));
	FGameplayTag SupplyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supply")
	int32 Amount = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Key")
	bool IsSupplied;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
