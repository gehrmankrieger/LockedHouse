// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKEDHOUSE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TryInteract();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	float InteractRange = 200.f;


	UPROPERTY(EditAnywhere, Category = "Interaction|Debug")
	bool bDrawDebug = true;

private:
	AActor* FindInteractable() const;
		
};
