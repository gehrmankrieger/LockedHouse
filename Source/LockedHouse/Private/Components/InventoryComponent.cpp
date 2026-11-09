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