// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryChangedSignature, FGameplayTag, Tag, bool, bAdded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSupplyChangedSignature, FGameplayTag, DelegateTag, int32, DelegateAmount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKEDHOUSE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChangedSignature OnInventoryChanged;

	UPROPERTY(BlueprintAssignable, Category = "Supply")
	FOnSupplyChangedSignature OnSupplyChanged;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasPickedUp(FGameplayTag Tag) const { return KeyTags.HasTagExact(Tag); }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool PickUp(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Drop(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Supply")
	bool AddSupply(FGameplayTag Tag, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Supply")
	bool UseSupply(FGameplayTag Tag, int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Supply")
	int32 GetSupplyCount(FGameplayTag Tag) const { return Supplies.FindRef(Tag); }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	FGameplayTagContainer KeyTags;

private:

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TMap<FGameplayTag, int32> Supplies;
	
};
