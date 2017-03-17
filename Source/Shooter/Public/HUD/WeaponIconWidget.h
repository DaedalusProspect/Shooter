// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"

#include "Public/Game/ShooterGameInstance.h"
#include "WeaponIconWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponItemClicked, int32, WeaponRefIndex, class UWeaponIconWidget*, WeaponWidget);

/**
 * 
 */
UCLASS()
class SHOOTER_API UWeaponIconWidget : public UUserWidget
{
	GENERATED_BODY()

		UWeaponIconWidget(const FObjectInitializer& ObjectInitializer);
		UWeaponIconWidget(const FObjectInitializer& ObjectInitializer, int32 WeaponRefIndex, bool InInventory);

	UButton* WeaponButton;
	UImage* WeaponImage;

	TSharedRef<SWidget> RebuildWidget() override;

	/* Copied from Parent. Unable to inherit. */
	/** Get World calls can be expensive for Widgets, we speed them up by caching the last found world until it goes away. */
	mutable TWeakObjectPtr<UWorld> CachedWorld;

public:

	virtual class UWorld* GetWorld() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, Meta = (ExposeOnSpawn = true))
	int32 WeaponItemRefIndex;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Weapon, Meta = (ExposeOnSpawn = true))
	bool bIsInInventory;
	
	UPROPERTY(BlueprintAssignable, Category = Weapon)
	FWeaponItemClicked OnWeaponItemClickedEvent;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void OnWeaponItemClicked(int32 WeaponIndex, UWeaponIconWidget* WeaponWidget);

	UFUNCTION(BlueprintPure, Category = Game)
	UShooterGameInstance* GetShooterGameInstance();


	UFUNCTION(BlueprintPure, Category = "Game UI")
	UButton* GetButton() { return WeaponButton; };

	UFUNCTION(BlueprintPure, Category = "Game UI")
	UImage* GetImage() { return WeaponImage; };

};
