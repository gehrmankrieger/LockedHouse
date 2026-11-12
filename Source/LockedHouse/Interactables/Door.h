// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "GameplayTagContainer.h"
#include "Door.generated.h"

class UTimelineComponent;

UCLASS()
class LOCKEDHOUSE_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UFUNCTION()
	void Swing(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(AActor* Interactor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	TObjectPtr<UStaticMeshComponent> FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	TObjectPtr<USceneComponent> Hinge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Door", meta = (Categories = "Item.Key"))
	FGameplayTag RequiredKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (Categories = "World.Door"))
	FGameplayTag UnlockedTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	bool bSealed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	TObjectPtr<UTimelineComponent> Timeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UCurveFloat* Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	float OpenAngle = 90.f;

	UPROPERTY()
	bool bIsOpen;

	UFUNCTION(BlueprintImplementableEvent, Category="Door")
	void OnLocked();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
