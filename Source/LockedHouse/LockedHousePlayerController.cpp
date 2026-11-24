// Copyright Epic Games, Inc. All Rights Reserved.


#include "LockedHousePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "LockedHouse.h"
#include "UI/LHHUDWidget.h"
#include "Components/InventoryComponent.h"
#include "Widgets/Input/SVirtualJoystick.h"

void ALockedHousePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (IsLocalPlayerController() && ShouldUseTouchControls())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogLockedHouse, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ALockedHousePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool ALockedHousePlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void ALockedHousePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsValid(InPawn) || !IsValid(HUDWidgetClass))
	{
		UE_LOG(LogLockedHouse, Warning, TEXT("HUDWidgetClass is not set in BP."));

		return;
	}
	
	if (!IsValid(HUDWidget))
	{
		HUDWidget = CreateWidget<ULHHUDWidget>(this, HUDWidgetClass);
		if (!IsValid(HUDWidget))
		{
			UE_LOG(LogLockedHouse, Error, TEXT("Error in creating HUDWidget."));
		}
		HUDWidget->AddToPlayerScreen();
	}

	UInventoryComponent* Inventory = InPawn->FindComponentByClass<UInventoryComponent>();

	if (!IsValid(Inventory))
	{
		UE_LOG(LogLockedHouse, Warning, TEXT("Invalid Inventory."));
		return;
	}

	HUDWidget->InitInventory(Inventory);

}
