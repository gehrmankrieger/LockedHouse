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

	OnItemPickup.Broadcast(Tag, StoreInInventory);

	return true;
}

void UInventoryComponent::Drop(FGameplayTag Tag)
{
	if (KeyTags.HasTagExact(Tag))
	{
		KeyTags.RemoveTag(Tag);
		UE_LOG(LogTemp, Warning, TEXT("%s is removed from Inventory."), *Tag.ToString());
	}

	OnItemPickup.Broadcast(Tag, StoreInInventory);
}