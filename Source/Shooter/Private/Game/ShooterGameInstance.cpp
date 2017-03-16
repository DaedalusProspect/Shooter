// Fill out your copyright notice in the Description page of Project Settings.

#include "Shooter.h"
#include "ShooterGameInstance.h"


bool UShooterGameInstance::CanAddWeaponToSelected()
{
	int32 HowManySelected = 0;

	for (auto& Itr : BackpackWeapons)
	{
		if (Itr.bIsSelected)
		{
			HowManySelected = HowManySelected + 1;
		}
	}

	if (HowManySelected < 3)
	{
		SetNumSelectedItems(HowManySelected);
		return true;
	}
	else
	{
		SetNumSelectedItems(HowManySelected);
		return false;
	}
}

void UShooterGameInstance::SetBackpackItemSelected(int32 BackpackIndex, bool Selected, int32 Slot)
{
	BackpackWeapons[BackpackIndex].bIsSelected = Selected;
	BackpackWeapons[BackpackIndex].Slot = Slot;
}

TArray<FWeaponItem> UShooterGameInstance::GetBackpack()
{
	return BackpackWeapons;
}

