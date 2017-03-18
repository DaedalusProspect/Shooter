// Fill out your copyright notice in the Description page of Project Settings.

#include "Shooter.h"
#include "WeaponInventoryWidget.h"


TSharedRef<SWidget> UWeaponInventoryWidget::RebuildWidget()
{
	RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
	UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);


	WidgetTree->RootWidget = RootWidget;

	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	if (RootWidget && WidgetTree)
	{
		// The main overlay
		TopOverlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("InventoryOverlay"));

		UPanelSlot* Slot1 = RootWidget->AddChild(TopOverlay);
		TopOverlaySlot = Cast<UCanvasPanelSlot>(Slot1);

		TopOverlaySlot->SetSize(FVector2D(950.0f, 635.0f));
		//

		// The scroll box for the main inventory
		TopScrollBox = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass(), TEXT("InventoryScrollBox"));

		UPanelSlot* Slot2 = TopOverlay->AddChild(TopScrollBox);
		TopScrollBoxSlot = Cast<UOverlaySlot>(Slot2);

		TopScrollBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		TopScrollBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		//

		// The GridPanel
		TopGridPanel = WidgetTree->ConstructWidget<UUniformGridPanel>(UUniformGridPanel::StaticClass(), TEXT("InventoryGridPanel"));
		
		UPanelSlot* Slot3 = TopScrollBox->AddChild(TopGridPanel);
		TopGridPanelSlot = Cast<UScrollBoxSlot>(Slot3);

		TopGridPanelSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);

		//
		//// End Top Part

		// Start bottom part

		BottomOverlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("EquipSlotOverlay"));

		UPanelSlot* Slot4 = RootWidget->AddChild(BottomOverlay);

		//


	}

	return Widget;
}

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