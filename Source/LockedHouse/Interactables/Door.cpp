// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Door.h"
#include "Components/InventoryComponent.h"
#include "Components/TimelineComponent.h"
#include "WorldStateSubsystem.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(SceneRoot);
	FrameMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FrameMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	FrameMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	Hinge = CreateDefaultSubobject<USceneComponent>(TEXT("Hinge"));
	Hinge->SetupAttachment(SceneRoot);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(Hinge);

	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat SwingUpdate;

	if (!IsValid(Curve))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Curve not set"), *GetName());
		return;
	}

	SwingUpdate.BindUFunction(this, FName("Swing"));
	Timeline->AddInterpFloat(Curve, SwingUpdate);
	
}

void ADoor::Interact_Implementation(AActor* Interactor)
{

	if (!IsValid(Interactor))
	{
		return;
	}

	UWorld* World = GetWorld();
	UWorldStateSubsystem* Board = World ? World->GetSubsystem<UWorldStateSubsystem>() : nullptr;

	if (!IsValid(Board))
	{
		UE_LOG(LogTemp, Warning, TEXT("NO BOARD."));
		return;
	}

	if (bSealed)
	{
		if (IsValid(GEngine))
		{
			GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::White, TEXT("It won't budge..."));
		}
		return;
	}
	

	if (!RequiredKey.IsValid() || !UnlockedTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: RequiredKey or UnlockedTag not set"), *GetName());
		return;
	}
	
	if (!Board->CheckDoorTag(UnlockedTag))
	{


		UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();

		if (!IsValid(Inventory))
		{
			return;
		}

		if (Inventory->HasPickedUp(RequiredKey))
		{
			Board->AddDoorTag(UnlockedTag);
			Inventory->Drop(RequiredKey);
		}
		else
		{
			if (IsValid(GEngine))
			{
				GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::White, TEXT("Locked..."));
			}
			OnLocked();
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s: unlocked, toggle here (step 6)"), *GetName());
	}

	if (Board->CheckDoorTag(UnlockedTag))
	{
		!bIsOpen ? Timeline->Play() : Timeline->Reverse();
		bIsOpen = !bIsOpen;
	}
	

	UE_LOG(LogTemp, Log, TEXT("Interacted with door %s, it needs %s"), *UnlockedTag.ToString(), *RequiredKey.ToString());
}

void ADoor::Swing(float Value)
{
	Hinge->SetRelativeRotation(FRotator(0.f, Value * OpenAngle, 0.f));
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

