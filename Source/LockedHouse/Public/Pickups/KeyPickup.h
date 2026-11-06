
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "GameplayTagContainer.h"
#include "KeyPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class LOCKEDHOUSE_API AKeyPickup : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AKeyPickup();

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void OnPickedUp(AActor* Collector);

protected:

	virtual void OnPickedUp_Implementation(AActor* Collector);

	virtual void Interact_Implementation(AActor* Collector) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Key")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Key")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key", meta = (Categories = "Item.Key"))
	FGameplayTag KeyTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Key")
	bool IsPickedUp;

};
