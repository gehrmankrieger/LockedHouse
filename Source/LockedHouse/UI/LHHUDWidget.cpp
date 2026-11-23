// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LHHUDWidget.h"
#include "Components/InventoryComponent.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "LockedHouseGameplayTags.h"

void ULHHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(Inventory))
	{
		Inventory->OnInventoryChanged.RemoveDynamic(this, &ULHHUDWidget::HandleInventoryChanged);

		Inventory->OnSupplyChanged.RemoveDynamic(this, &ULHHUDWidget::HandleSupplyChanged);
	}

}

void ULHHUDWidget::InitInventory(UInventoryComponent* InInventory)
{
	Inventory = InInventory;
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Inventory."));
		return;
	}

	Inventory->OnInventoryChanged.AddDynamic(this, &ULHHUDWidget::HandleInventoryChanged);
	Inventory->OnSupplyChanged.AddDynamic(this, &ULHHUDWidget::HandleSupplyChanged);

	RebuildKeyList();
	RefreshCounts();
}

void ULHHUDWidget::RebuildKeyList()
{
	if (!IsValid(KeyList))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid KeyList."));
		return;
	}

	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Inventory."));
		return;
	}
	KeyList->ClearChildren();
	for (const FGameplayTag& Tag : Inventory->GetKeys().GetGameplayTagArray())
	{
		UTextBlock* Line = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		FText* Found = KeyNames.Find(Tag);
		Found ? Line->SetText(*Found) : Line->SetText(FText::FromString(Tag.ToString()));
	}
}

void ULHHUDWidget::RefreshCounts()
{
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Inventory."));
		return;
	}

	if (!IsValid(BandageCountText))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Bandage Count."));
		return;
	}

	if (!IsValid(AmmoCountText))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Ammo Count."));
		return;
	}

	BandageCountText->SetText(FText::AsNumber(Inventory->GetSupplyCount(LockedHouseTags::Item_Supply_Bandage)));
	AmmoCountText->SetText(FText::AsNumber(Inventory->GetSupplyCount(LockedHouseTags::Item_Supply_Ammo)));
}

void ULHHUDWidget::HandleInventoryChanged(FGameplayTag Tag, bool bAdded)
{
	RebuildKeyList();
}

void ULHHUDWidget::HandleSupplyChanged(FGameplayTag ChangedTag, int32 NewCount)
{
	RefreshCounts();
}
