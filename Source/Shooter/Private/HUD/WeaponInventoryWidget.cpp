// Fill out your copyright notice in the Description page of Project Settings.

#include "Shooter.h"
#include "WeaponInventoryWidget.h"




class UWorld* UWeaponInventoryWidget::GetWorld() const
{

	if (UWorld* LastWorld = CachedWorld.Get())
	{
		return LastWorld;
	}

	if (HasAllFlags(RF_ClassDefaultObject))
	{
		// If we are a CDO, we must return nullptr instead of calling Outer->GetWorld() to fool UObject::ImplementsGetWorld.
		return nullptr;
	}

	UObject* Outer = GetOuter();

	while (Outer)
	{
		UWorld* World = Outer->GetWorld();
		if (World)
		{
			CachedWorld = World;
			return World;
		}

		Outer = Outer->GetOuter();
	}

	return nullptr;
}

UShooterGameInstance* UWeaponInventoryWidget::GetShooterGameInstance()
{

	UShooterGameInstance* GI = Cast<UShooterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	return GI;

}