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

	UPanelWidget* RootWidget;
	
	// Top Panel
	UOverlay* TopOverlay;
	UBorder* TopBorder;
	UScrollBox* TopScrollBox;
	UUniformGridPanel* TopGridPanel;

	// Bottom Panel
	UOverlay* BottomOverlay;
	UBorder* BottomBorder;
	UHorizontalBox* BottomBox;
	UOverlay* WeaponSlot1;
	UOverlay* WeaponSlot2;
	UOverlay* WeaponSlot3;

	// The slots for everything

	// Top
	UCanvasPanelSlot* TopOverlaySlot;
	UOverlaySlot* TopScrollBoxSlot;
	UScrollBoxSlot* TopGridPanelSlot;


public:

	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual class UWorld* GetWorld() const override;

	UFUNCTION(BlueprintPure, Category = Game)
	UShooterGameInstance* GetShooterGameInstance();
	
};
