// Fill out your copyright notice in the Description page of Project Settings.

#include "Shooter.h"
#include "GameFramework/InputSettings.h"
#include "Blueprint/UserWidget.h"
#include "GameplayPlayerController.h"



AGameplayPlayerController::AGameplayPlayerController()
{
	ControllingDevice = FControllingDeviceType::CD_Mouse;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	MouseSensitivityMin = 0.0f;
	MouseSensitivityMax = 2.0f;
	CurrentMouseSensitivity = 1.0f;

	TouchSensitivityMin = 5.0f;
	TouchSensitivityMax = 15.0f;
	CurrentTouchSensitivity = 10.0f;

	GyroSensitivityMin = 20.0f;
	GyroSensitivityMax = 60.0f;
	CurrentGyroSensitivity = 40.0f;

	bSensitivityMenuActive = false;
	DebugSensitivityMenu = nullptr;

}

void AGameplayPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Turn", this, &AGameplayPlayerController::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &AGameplayPlayerController::AddPitchInput);

	InputComponent->BindAction("DebugMenuSensitivity", IE_Pressed, this, &AGameplayPlayerController::ToggleSensitivityMenu);

}

void AGameplayPlayerController::ToggleSensitivityMenu()
{
	if (IsLocalPlayerController())
	{
		if (DebugSensitivityMenu == nullptr)
		{

			if (wDebugSensitivity.LoadSynchronous())
			{


				DebugSensitivityMenu = CreateWidget<UUserWidget>(this, wDebugSensitivity.LoadSynchronous());

				if (!DebugSensitivityMenu)
					return;

				DebugSensitivityMenu->AddToViewport();


				FInputModeUIOnly UIOnlyMode;
				UIOnlyMode.SetWidgetToFocus(DebugSensitivityMenu->GetCachedWidget());
				SetInputMode(UIOnlyMode);
				bShowMouseCursor = true;

				bSensitivityMenuActive = true;

				return;
			}


		}
		if (DebugSensitivityMenu)
		{

			DebugSensitivityMenu->RemoveFromViewport();
			DebugSensitivityMenu = nullptr;
			FInputModeGameOnly GameOnlyMode;
			SetInputMode(GameOnlyMode);
			bShowMouseCursor = false;

			bSensitivityMenuActive = false;

		}
	}
}

float AGameplayPlayerController::GetSensitivity(FControllingDeviceType Device, bool isCurrentDevice)
{
	float LocalSensitivity = 0;

	if (isCurrentDevice)
	{
		switch (ControllingDevice)
		{
		case FControllingDeviceType::CD_Mouse:
			LocalSensitivity = CurrentMouseSensitivity;
			break;
		case FControllingDeviceType::CD_Touch:
			LocalSensitivity = CurrentTouchSensitivity;
			break;
		case FControllingDeviceType::CD_Gyro:
			LocalSensitivity = CurrentGyroSensitivity;
			break;
		}
	}
	else
	{
		switch (Device)
		{
		case FControllingDeviceType::CD_Mouse:
			LocalSensitivity = CurrentMouseSensitivity;
			break;
		case FControllingDeviceType::CD_Touch:
			LocalSensitivity = CurrentTouchSensitivity;
			break;
		case FControllingDeviceType::CD_Gyro:
			LocalSensitivity = CurrentGyroSensitivity;
			break;
		}
	}

	return LocalSensitivity;
}

void AGameplayPlayerController::SetSensitivity(FControllingDeviceType Device, float NewSensitivity)
{
	switch (Device)
	{
	case FControllingDeviceType::CD_Mouse:
		CurrentMouseSensitivity = NewSensitivity;
		break;
	case FControllingDeviceType::CD_Touch:
		CurrentTouchSensitivity = NewSensitivity;
		break;
	case FControllingDeviceType::CD_Gyro:
		CurrentGyroSensitivity = NewSensitivity;
		break;
	}
}


void AGameplayPlayerController::AddPitchInput(float Val)
{
	if (ControllingDevice == FControllingDeviceType::CD_Mouse)
	{
		Super::AddPitchInput(Val * CurrentMouseSensitivity);
	}
	else

	{
		Super::AddPitchInput(Val);
	}
	
}

void AGameplayPlayerController::AddYawInput(float Val)
{
	if (ControllingDevice == FControllingDeviceType::CD_Mouse)
	{
		Super::AddYawInput(Val * CurrentMouseSensitivity);
	}
	else

	{
		Super::AddYawInput(Val);
	}
}

void AGameplayPlayerController::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AGameplayPlayerController::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
	}
	TouchItem.bIsPressed = false;
}

//This allows the user to turn without using the right virtual joystick

void AGameplayPlayerController::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddYawInput(Value);
					}
					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y * BaseTurnRate;
						AddPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void AGameplayPlayerController::HandleTilt(const FVector Val)
{
	if (ControllingDevice == FControllingDeviceType::CD_Gyro)
	{
		FVector Delta = (Val * CurrentGyroSensitivity) - LastTilt;
		AddPitchInput(Delta.Z);
		AddYawInput(Delta.X * -1.0);
	}
}