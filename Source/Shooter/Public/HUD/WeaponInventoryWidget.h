// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"

#include "Public/Game/ShooterGameInstance.h"
#include "Public/HUD/WeaponIconWidget.h"

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
	UPanelWidget* RootWidget;
	
	// Top Panel
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UOverlay* TopOverlay;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UBorder* TopBorder;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UScrollBox* TopScrollBox;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UUniformGridPanel* TopGridPanel;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UCanvasPanelSlot* TopOverlaySlot;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UOverlaySlot* TopBorderSlot;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UBorderSlot* TopScrollBoxSlot;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UScrollBoxSlot* TopGridPanelSlot;

	// Bottom Panel

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UOverlay* BottomOverlay;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UBorder* BottomBorder;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UHorizontalBox* BottomBox;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UOverlay* WeaponSlot1;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UOverlay* WeaponSlot2;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	UOverlay* WeaponSlot3;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UCanvasPanelSlot* BottomOverlaySlot;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UOverlaySlot* BottomBorderSlot;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UBorderSlot* BottomBoxSlot;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UHorizontalBoxSlot* WeaponSelectSlot1;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UHorizontalBoxSlot* WeaponSelectSlot2;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	UHorizontalBoxSlot* WeaponSelectSlot3;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	TArray<UWeaponIconWidget*> InventoryWeapons;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	TArray<UPanelSlot*> InventorySlots;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slots", meta = (ShowOnlyInnerProperties))
	TArray<UUniformGridSlot*> InventoryGridSlots;


	/* Info */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	bool bFirstSlotTaken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	bool bSecondSlotTaken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	bool bThirdSlotTaken;



public:

	UWeaponInventoryWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnWidgetRebuilt() override;

	virtual class UWorld* GetWorld() const override;

	UFUNCTION(BlueprintPure, Category = Game)
	UShooterGameInstance* GetShooterGameInstance();
	

	UFUNCTION(BlueprintCallable)
	int FindFirstFreeSlot();

	UFUNCTION(BlueprintCallable)
	void CreateBackpack(bool bWithoutWeapons);

	UFUNCTION(BlueprintCallable)
	void ItemClickedInBackpack(int32 WeaponRefIndex, UWeaponIconWidget* WidgetRef);

	UFUNCTION(BlueprintCallable)
	void ItemClickedInSelected(int32 WeaponRefIndex, UWeaponIconWidget* WidgetRef);
};
