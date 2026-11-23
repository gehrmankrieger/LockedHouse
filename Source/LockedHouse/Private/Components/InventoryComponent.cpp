#include "Components/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	
}

bool UInventoryComponent::PickUp(FGameplayTag Tag)
{	
	if (!Tag.IsValid())
	{
		return false;
	}


	KeyTags.AddTag(Tag);
	UE_LOG(LogTemp, Warning, TEXT("%s added to Inventory: %d"), *Tag.ToString(), HasPickedUp(Tag));

	OnInventoryChanged.Broadcast(Tag, true);

	return true;
}

void UInventoryComponent::Drop(FGameplayTag Tag)
{
	if (KeyTags.RemoveTag(Tag))
	{
		UE_LOG(LogTemp, Log, TEXT("%s is removed from Inventory."), *Tag.ToString());
		OnInventoryChanged.Broadcast(Tag, false);

	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't remove %s from Inventory."), *Tag.ToString());
	}
}

/* Refactor, similarities with PickUp. */
bool UInventoryComponent::AddSupply(FGameplayTag Tag, int32 Amount)
{
	if (!Tag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Tag: %s."), *Tag.ToString());
		return false;
	}

	if (Amount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Amount %d for %s."), Amount, *Tag.ToString());
		return false;
	}

	Supplies.FindOrAdd(Tag) += Amount;
	OnSupplyChanged.Broadcast(Tag, Supplies.FindRef(Tag));
	UE_LOG(LogTemp, Log, TEXT("Supply added: %s. %d available."), *Tag.ToString(), Supplies.FindRef(Tag));
	return true;
}

bool UInventoryComponent::UseSupply(FGameplayTag Tag, int32 Amount)
{
	if (!Tag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Tag: %s."), *Tag.ToString());
		return false;
	}

	if (Amount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Amount %d for %s."), Amount, *Tag.ToString());
		return false;
	}

	if (GetSupplyCount(Tag) < Amount)
	{
		UE_LOG(LogTemp, Log, TEXT("Insufficient Supply: %s."), *Tag.ToString());
		return false;
	}

	Supplies.FindOrAdd(Tag) -= Amount;
	OnSupplyChanged.Broadcast(Tag, Supplies.FindRef(Tag));
	UE_LOG(LogTemp, Log, TEXT("Supply used: %s."), *Tag.ToString());
	return true;
}
