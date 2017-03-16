// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Public/Weapon/WeaponItem.h"
#include "ShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:

	int32 TotalSelectedItems;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
		TArray<FWeaponItem> BackpackWeapons;

	UFUNCTION(BlueprintCallable)
	void SetNumSelectedItems(int32 Num) { TotalSelectedItems = Num; };
	
	UFUNCTION(BlueprintPure)
	int32 GetNumSelectedItems() { return TotalSelectedItems; };

	UFUNCTION(BlueprintPure)
	TArray<FWeaponItem> GetBackpack();

	UFUNCTION(BlueprintPure)
	bool CanAddWeaponToSelected();

	UFUNCTION(BlueprintCallable)
	void SetBackpackItemSelected(int32 BackpackIndex, bool bIsSelected, int32 Slot);
	
};
