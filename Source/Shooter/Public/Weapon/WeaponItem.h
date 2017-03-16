// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponItem.generated.h"


USTRUCT(BlueprintType)
struct FWeaponItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	TSubclassOf<AActor> WeaponToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	UTexture2D* BackpackImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	bool bIsSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	int32 Slot;

	FWeaponItem()
	{
		WeaponToSpawn = nullptr;
		BackpackImage = nullptr;
		bIsSelected = false;
		Slot = 0;
	}
};
/**
 * 
 */
