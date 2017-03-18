// Fill out your copyright notice in the Description page of Project Settings.

#include "Shooter.h"
#include "WeaponIconWidget.h"

UWeaponIconWidget::UWeaponIconWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

UWeaponIconWidget::UWeaponIconWidget(const FObjectInitializer& ObjectInitializer, int32 WeaponRefIndex, bool InInventory) : Super(ObjectInitializer)
{
	WeaponItemRefIndex = WeaponRefIndex;
	bIsInInventory = InInventory;
}


TSharedRef<SWidget> UWeaponIconWidget::RebuildWidget()
{

	RootWidget = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("Root Overlay"));
	UOverlaySlot* RootWidgetSlot = Cast<UOverlaySlot>(RootWidget->Slot);


	WidgetTree->RootWidget = RootWidget;

	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	if (RootWidget && WidgetTree)
	{
		// Get our game instance
		UShooterGameInstance* GI = Cast<UShooterGameInstance>(GetWorld()->GetGameInstance());
		TArray<FWeaponItem> BP;
		if (GI)
		{
			BP = GI->BackpackWeapons;
		}

		// Create the button

		WeaponButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("ItemButton"));
		/*FButtonStyle ButtonStyle = WeaponButton->WidgetStyle.GetDefault().;
		FSlateBrush ButtonBrush;
		ButtonBrush.ImageSize = FVector2D(150.0f, 150.0f);
		ButtonStyle.SetHovered(ButtonBrush);
		ButtonStyle.SetNormal(ButtonBrush);
		ButtonStyle.SetPressed(ButtonBrush);
		WeaponButton->SetStyle(ButtonStyle);*/
		WeaponButton->WidgetStyle.Hovered.ImageSize = FVector2D(150.0f, 150.0f);
		WeaponButton->WidgetStyle.Normal.ImageSize = FVector2D(150.0f, 150.0f);
		WeaponButton->WidgetStyle.Pressed.ImageSize = FVector2D(150.0f, 150.0f);
		//WeaponButton->OnClicked.Add(OnWeaponItemClickedEvent);

		UPanelSlot* Slot1 = RootWidget->AddChild(WeaponButton);
		UOverlaySlot* ButtonSlot = Cast<UOverlaySlot>(Slot1);

		// Create the image overlay
		WeaponImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		if (BP.Num() != 0)
		{
			WeaponImage->SetBrushFromTexture(BP[0].BackpackImage, false);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(BP.Num()));
			
		}
		WeaponImage->SetColorAndOpacity(FLinearColor(1.0, 1.0, 1.0, 1.0));
		WeaponImage->Visibility = ESlateVisibility::HitTestInvisible;
		WeaponImage->Brush.ImageSize = FVector2D(130.0f, 130.0f);

		// Start building the widget

		UPanelSlot* Slot2 = RootWidget->AddChild(WeaponImage);
		UOverlaySlot* ImageSlot = Cast<UOverlaySlot>(Slot2);

		ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

		ImageSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		ImageSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

		
	}

	return Widget;
}

UShooterGameInstance* UWeaponIconWidget::GetShooterGameInstance()
{
	
	UShooterGameInstance* GI = Cast<UShooterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	return GI;

}

class UWorld* UWeaponIconWidget::GetWorld() const
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

void UWeaponIconWidget::OnWeaponItemClicked(int32 WeaponIndex, UWeaponIconWidget* WeaponWidget)
{
	if (OnWeaponItemClickedEvent.IsBound())
	{
		OnWeaponItemClickedEvent.Broadcast(WeaponIndex, WeaponWidget);
	}
}
