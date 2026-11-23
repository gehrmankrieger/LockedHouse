#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "LHHUDWidget.generated.h"

class UInventoryComponent;
class UVerticalBox;
class UTextBlock;

UCLASS()
class LOCKEDHOUSE_API ULHHUDWidget : public UUserWidget
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	TObjectPtr<UVerticalBox> KeyList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> BandageCountText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> AmmoCountText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TMap<FGameplayTag, FText> KeyNames;

	virtual void NativeDestruct() override;


public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	void InitInventory(UInventoryComponent* InInventory);

private:

	UPROPERTY()
	TObjectPtr<UInventoryComponent> Inventory;

	UFUNCTION()
	void RebuildKeyList();

	UFUNCTION()
	void RefreshCounts();

	UFUNCTION()
	void HandleInventoryChanged(FGameplayTag Tag, bool bAdded);

	UFUNCTION()
	void HandleSupplyChanged(FGameplayTag ChangedTag, int32 NewCount);
};