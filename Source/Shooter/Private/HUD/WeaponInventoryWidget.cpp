// Fill out your copyright notice in the Description page of Project Settings.

#include "Shooter.h"
#include "WeaponInventoryWidget.h"



UWeaponInventoryWidget::UWeaponInventoryWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{


}

void UWeaponInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CreateBackpack(false);
}



TSharedRef<SWidget> UWeaponInventoryWidget::RebuildWidget()
{
	RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
	UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);


	WidgetTree->RootWidget = RootWidget;

	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	if (RootWidget && WidgetTree)
	{

		// Setup some brushes for design
		FSlateBrush BorderBrush;
		BorderBrush.DrawAs = ESlateBrushDrawType::Border;
		BorderBrush.Margin = 1.0f;

		// The main overlay
		TopOverlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("InventoryOverlay"));
		TopOverlay->bHiddenInDesigner = false;
		TopOverlay->bExpandedInDesigner = true;

		UPanelSlot* Slot1 = RootWidget->AddChild(TopOverlay);
		TopOverlaySlot = Cast<UCanvasPanelSlot>(Slot1);


		TopOverlaySlot->SetSize(FVector2D(705.0f, 355.0f));
		//

		// The border
		TopBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("InventoryBorder"));

		UPanelSlot* Slot2 = TopOverlay->AddChild(TopBorder);
		TopBorderSlot = Cast<UOverlaySlot>(Slot2);


		TopBorder->SetBrush(BorderBrush);
		TopBorder->SetBrushColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		TopBorderSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		TopBorderSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		//

		// The scroll box for the main inventory
		TopScrollBox = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass(), TEXT("InventoryScrollBox"));

		UPanelSlot* Slot3 = TopBorder->AddChild(TopScrollBox);
		TopScrollBoxSlot = Cast<UBorderSlot>(Slot3);

		TopScrollBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		TopScrollBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		//

		// The GridPanel
		TopGridPanel = WidgetTree->ConstructWidget<UUniformGridPanel>(UUniformGridPanel::StaticClass(), TEXT("InventoryGridPanel"));

		
		UPanelSlot* Slot4 = TopScrollBox->AddChild(TopGridPanel);
		TopGridPanelSlot = Cast<UScrollBoxSlot>(Slot4);
		TopGridPanelSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);

		//
		//// End Top Part

		// Start bottom part

		BottomOverlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("EquipSlotOverlay"));

		UPanelSlot* Slot5 = RootWidget->AddChild(BottomOverlay);
		BottomOverlaySlot = Cast<UCanvasPanelSlot>(Slot5);

		BottomOverlaySlot->SetPosition(FVector2D(0.0f, 400.0f));
		BottomOverlaySlot->SetSize(FVector2D(705.0f, 180.0f));
		//

		// Bottom Border
		BottomBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("BottomBorder"));

		BottomBorder->SetBrush(BorderBrush);
		UPanelSlot* Slot6 = BottomOverlay->AddChild(BottomBorder);
		BottomBorderSlot = Cast<UOverlaySlot>(Slot6);

		BottomBorderSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		BottomBorderSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		//

		// Bottom Horizontal Box
		BottomBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass(), TEXT("BottomHorizontalBox"));

		UPanelSlot* Slot7 = BottomBorder->AddChild(BottomBox);
		BottomBoxSlot = Cast<UBorderSlot>(Slot7);

		BottomBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		BottomBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		
		///

		// Weapon Slot 1
		WeaponSlot1 = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("WeaponSlot1"));

		UPanelSlot* Slot8 = BottomBox->AddChildToHorizontalBox(WeaponSlot1);
		WeaponSelectSlot1 = Cast<UHorizontalBoxSlot>(Slot8);

		FSlateChildSize SlotSize;
		SlotSize.SizeRule = ESlateSizeRule::Fill;
		SlotSize.Value = 1.0f;

		WeaponSelectSlot1->SetSize(SlotSize);
		WeaponSelectSlot1->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		WeaponSelectSlot1->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		//

		// Weapon Slot 2

		WeaponSlot2 = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("WeaponSlot2"));

		UPanelSlot* Slot9 = BottomBox->AddChildToHorizontalBox(WeaponSlot2);
		WeaponSelectSlot2 = Cast<UHorizontalBoxSlot>(Slot9);

		WeaponSelectSlot2->SetSize(SlotSize);
		WeaponSelectSlot2->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		WeaponSelectSlot2->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		//

		//WEapon Slot 3

		WeaponSlot3 = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("WeaponSlot3"));

		UPanelSlot* Slot10 = BottomBox->AddChildToHorizontalBox(WeaponSlot3);
		WeaponSelectSlot3 = Cast<UHorizontalBoxSlot>(Slot10);

		WeaponSelectSlot3->SetSize(SlotSize);
		WeaponSelectSlot3->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		WeaponSelectSlot3->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		//

	}

	return Widget;
}

void UWeaponInventoryWidget::OnWidgetRebuilt()
{
	// When a user widget is rebuilt we can safely initialize the navigation now since all the slate
	// widgets should be held onto by a smart pointer at this point.
	WidgetTree->ForEachWidget([&](UWidget* Widget) {
		Widget->BuildNavigation();
	});

	if (!IsDesignTime())
	{
		// Notify the widget that it has been constructed.
		NativeConstruct();
	}
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

int UWeaponInventoryWidget::FindFirstFreeSlot()
{
	int CurrentFreeSlot;

	if (!bFirstSlotTaken)
	{
		CurrentFreeSlot = 1;
		return CurrentFreeSlot;
	}

	if (!bSecondSlotTaken)
	{
		CurrentFreeSlot = 2;
		return CurrentFreeSlot;
	}

	if (!bThirdSlotTaken)
	{
		CurrentFreeSlot = 3;
		return CurrentFreeSlot;
	}

	return 0;

}

void UWeaponInventoryWidget::CreateBackpack(bool bWithoutWeapons)
{
	// Clear the grid of anything so we can build it

	TopGridPanel->ClearChildren();
	InventoryWeapons.Empty();
	InventorySlots.Empty();
	InventoryGridSlots.Empty();

	int row = 0; // Keeps track of the row to add to
	int column = 0;

	// Lets get our backpack
	UShooterGameInstance* GI = Cast<UShooterGameInstance>(GetWorld()->GetGameInstance());
	if (GI == nullptr)
	{
		return;
	}


	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(GI->GetBackpack().Num()));

	
	for (int i = 0; i < GI->GetBackpack().Num(); ++i)
	{
		UWeaponIconWidget* InventoryWeapon = WidgetTree->ConstructWidget<UWeaponIconWidget>(UWeaponIconWidget::StaticClass(), NAME_None));
		InventoryWeapon->WeaponItemRefIndex = i;
		InventoryWeapon->bIsInInventory = false;

		InventoryWeapon->UpdateImage();
		InventoryWeapon->OnWeaponItemClickedEvent.AddDynamic(this, &UWeaponInventoryWidget::ItemClickedInBackpack);

		UPanelSlot* InventorySlot = TopGridPanel->AddChild(InventoryWeapon);


		if (InventorySlots[i])
		{
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SIGH"));
		}

		UUniformGridSlot* InventoryGridSlot = Cast<UUniformGridSlot>(InventorySlot);

		if (InventoryGridSlots[i])
		{
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SIGH"));
		}

		column = i;
		if (column > 2)
		{
			column = column - 3;
			if (row == 0)
				row++;
		}
		InventoryGridSlot->SetColumn(column % 3);
		InventoryGridSlot->SetRow(row);
		
		if (!bWithoutWeapons)
		{
			if (GI->GetBackpack()[i].bIsSelected)
			{
				UWeaponIconWidget* SelectedWeapon = WidgetTree->ConstructWidget<UWeaponIconWidget>(UWeaponIconWidget::StaticClass(), NAME_None);
				SelectedWeapon->WeaponItemRefIndex = i;
				SelectedWeapon->UpdateImage();
				SelectedWeapon->bIsInInventory = true;
				SelectedWeapon->OnWeaponItemClickedEvent.AddDynamic(this, &UWeaponInventoryWidget::ItemClickedInSelected);

				UPanelSlot* SlotS;
				UOverlaySlot* SelectedSlot;

				switch (GI->GetBackpack()[i].Slot)
				{
				case 1:
					SlotS = WeaponSlot1->AddChild(SelectedWeapon);
					SelectedSlot = Cast<UOverlaySlot>(SlotS);
					bFirstSlotTaken = true;

					SelectedSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
					SelectedSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
					break;

				case 2:
					SlotS = WeaponSlot2->AddChild(SelectedWeapon);
					SelectedSlot = Cast<UOverlaySlot>(SlotS);
					bSecondSlotTaken = true;

					SelectedSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
					SelectedSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
					break;

				case 3:
					SlotS = WeaponSlot3->AddChild(SelectedWeapon);
					SelectedSlot = Cast<UOverlaySlot>(SlotS);
					bThirdSlotTaken = true;

					SelectedSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
					SelectedSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
					break;
				}
				
			}
			
		}
		

	}
}

void UWeaponInventoryWidget::ItemClickedInBackpack(int32 WeaponRefIndex, UWeaponIconWidget* WidgetRef)
{
	// Lets get our backpack
	UShooterGameInstance* GI = Cast<UShooterGameInstance>(GetWorld()->GetGameInstance());
	if (GI == nullptr)
	{
		return;
	}

	if (GI->GetBackpack()[WeaponRefIndex].bIsSelected)
	{
		GI->GetBackpack()[WeaponRefIndex].bIsSelected = false;
		CreateBackpack(true);
	}
	else
	{
		if (GI->CanAddWeaponToSelected())
		{
			int32 FreeSlot = FindFirstFreeSlot();
			GI->SetBackpackItemSelected(WeaponRefIndex, true, FreeSlot);
			CreateBackpack(true);

			UWeaponIconWidget* SelectedWeapon = WidgetTree->ConstructWidget<UWeaponIconWidget>(UWeaponIconWidget::StaticClass(), NAME_None);
			SelectedWeapon->WeaponItemRefIndex = WeaponRefIndex;
			SelectedWeapon->bIsInInventory = true;
			SelectedWeapon->UpdateImage();

			SelectedWeapon->OnWeaponItemClickedEvent.AddDynamic(this, &UWeaponInventoryWidget::ItemClickedInSelected);


			UPanelSlot* SlotS;
			UOverlaySlot* SelectedSlot;

			switch (FreeSlot)
			{
			case 1:
				SlotS = WeaponSlot1->AddChild(SelectedWeapon);
				SelectedSlot = Cast<UOverlaySlot>(SlotS);
				bFirstSlotTaken = true;

				SelectedSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				SelectedSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				break;

			case 2:
				SlotS = WeaponSlot2->AddChild(SelectedWeapon);
				SelectedSlot = Cast<UOverlaySlot>(SlotS);
				bSecondSlotTaken = true;

				SelectedSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				SelectedSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				break;

			case 3:
				SlotS = WeaponSlot3->AddChild(SelectedWeapon);
				SelectedSlot = Cast<UOverlaySlot>(SlotS);
				bThirdSlotTaken = true;

				SelectedSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				SelectedSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				break;
			}
			

		}
	}
}

void UWeaponInventoryWidget::ItemClickedInSelected(int32 WeaponRefIndex, UWeaponIconWidget* WidgetRef)
{
	UShooterGameInstance* GI = Cast<UShooterGameInstance>(GetWorld()->GetGameInstance());
	if (GI == nullptr)
	{
		return;
	}

	switch (GI->GetBackpack()[WeaponRefIndex].Slot)
	{
	case 1:
		bFirstSlotTaken = false;
		break;
	case 2:
		bSecondSlotTaken = false;
		break;
	case 3:
		bThirdSlotTaken = false;
		break;
	}

	GI->SetBackpackItemSelected(WeaponRefIndex, false, 0);
	CreateBackpack(true);

	WidgetRef->RemoveFromParent();
}

