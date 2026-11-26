// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponComponent::Fire()
{
}

void UWeaponComponent::Reload()
{
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

