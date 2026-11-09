// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryChangedSignature, FGameplayTag, Tag, bool, bAdded);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKEDHOUSE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChangedSignature OnInventoryChanged;


	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasPickedUp(FGameplayTag Tag) const { return KeyTags.HasTagExact(Tag); }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool PickUp(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Drop(FGameplayTag Tag);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	FGameplayTagContainer KeyTags;
	
};
