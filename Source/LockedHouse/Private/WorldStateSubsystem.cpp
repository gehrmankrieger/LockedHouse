// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldStateSubsystem.h"

void UWorldStateSubsystem::AddDoorTag(FGameplayTag Tag)
{
	if (!Tag.IsValid())
	{
		return;
	}

	UnlockedDoorTags.AddTag(Tag);
}

bool UWorldStateSubsystem::CheckDoorTag(FGameplayTag Tag)
{
	if (UnlockedDoorTags.HasTagExact(Tag))
	{
		return true;
	}

	return false;
}
