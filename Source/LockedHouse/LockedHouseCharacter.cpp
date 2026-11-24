// Copyright Epic Games, Inc. All Rights Reserved.

#include "LockedHouseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/HealthComponent.h"
#include "LockedHouseGameplayTags.h"
#include "LockedHouse.h"

ALockedHouseCharacter::ALockedHouseCharacter()
{
	// Set Aim Timeline
	AimTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AimTimeline"));

	// Set camera pose settings based on view type (Explore/Aim)
	ExplorePose.ArmLength = 220.f;
	ExplorePose.SocketOffset = FVector(0, 45, 20);
	ExplorePose.FOV = 90.f;

	AimPose.ArmLength = 110.f;
	AimPose.SocketOffset = FVector(0, 55, 10);
	AimPose.FOV = 70.f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetOffset = FVector(0, 0, 50);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10;
	CameraBoom->CameraLagMaxDistance = 40;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ALockedHouseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALockedHouseCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ALockedHouseCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALockedHouseCharacter::Look);

		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ALockedHouseCharacter::StartAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ALockedHouseCharacter::StopAim);

		// Bandaging
		EnhancedInputComponent->BindAction(UseBandageAction, ETriggerEvent::Started, this, &ALockedHouseCharacter::UseBandage);
	}
	else
	{
		UE_LOG(LogLockedHouse, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALockedHouseCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateMovementMode();
	FOnTimelineFloat AimUpdate;

	CameraBoom->TargetArmLength = ExplorePose.ArmLength;
	CameraBoom->SocketOffset = ExplorePose.SocketOffset;
	FollowCamera->SetFieldOfView(ExplorePose.FOV);

	if (!IsValid(Curve))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Curve not set"), *GetName());
		return;
	}

	AimUpdate.BindUFunction(this, "UpdateAimBlend");
	AimTimeline->AddInterpFloat(Curve, AimUpdate);


}

void ALockedHouseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ALockedHouseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ALockedHouseCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ALockedHouseCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ALockedHouseCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ALockedHouseCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void ALockedHouseCharacter::UpdateAimBlend(float Alpha)
{
	CameraBoom->TargetArmLength = FMath::Lerp(ExplorePose.ArmLength, AimPose.ArmLength, Alpha);
	CameraBoom->SocketOffset = FMath::Lerp(ExplorePose.SocketOffset, AimPose.SocketOffset, Alpha);
	FollowCamera->SetFieldOfView(FMath::Lerp(ExplorePose.FOV, AimPose.FOV, Alpha));
}

void ALockedHouseCharacter::StartAim()
{
	bIsAiming = true;
	AimTimeline->Play();
	UpdateMovementMode();
}

void ALockedHouseCharacter::StopAim()
{
	bIsAiming = false;
	AimTimeline->Reverse();
	UpdateMovementMode();
}

void ALockedHouseCharacter::UpdateMovementMode()
{
	if (IsAiming())
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->MaxWalkSpeed = AimSpeed;
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->MaxWalkSpeed = ExploreSpeed;
	}
}

void ALockedHouseCharacter::UseBandage()
{
	UInventoryComponent* Inventory = FindComponentByClass<UInventoryComponent>();
	
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Inventory Component: %s"), *GetName());
		return;
	}

	UHealthComponent* Health = FindComponentByClass<UHealthComponent>();

	if (!IsValid(Health))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Health Component: %s"), *GetName());
		return;
	}

	if (Health->IsFull())
	{
		UE_LOG(LogTemp, Log, TEXT("Health is full: %.0f/%.0f"), Health->GetHealth(), Health->GetMaxHealth());
		return;
	}

	if (!Inventory->UseSupply(LockedHouseTags::Item_Supply_Bandage))
	{
		UE_LOG(LogTemp, Warning, TEXT("No bandages."));
		return;

	}

	Health->Heal(BandageHealAmount);

	UE_LOG(LogTemp, Warning, TEXT("Healed for %.0f. Health is now %.0f."), BandageHealAmount, Health->GetHealth());

}
