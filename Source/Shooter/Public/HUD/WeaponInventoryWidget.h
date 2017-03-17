// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"

#include "Public/Game/ShooterGameInstance.h"

#include "WeaponInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UWeaponInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Copied from Parent. Unable to inherit. */
	/** Get World calls can be expensive for Widgets, we speed them up by caching the last found world until it goes away. */
	mutable TWeakObjectPtr<UWorld> CachedWorld;
	

public:

	virtual class UWorld* GetWorld() const override;

	UFUNCTION(BlueprintPure, Category = Game)
	UShooterGameInstance* GetShooterGameInstance();
	
};
