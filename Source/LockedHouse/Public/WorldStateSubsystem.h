// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "WorldStateSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LOCKEDHOUSE_API UWorldStateSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Tags")
	void AddDoorTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Tags")
	bool CheckDoorTag(FGameplayTag Tag);

	const FGameplayTagContainer& GetAllDoorTags() const { return UnlockedDoorTags; }

private:
	UPROPERTY()
	FGameplayTagContainer UnlockedDoorTags;

};
