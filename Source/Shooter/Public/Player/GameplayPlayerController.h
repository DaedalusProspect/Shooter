// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "GameplayPlayerController.generated.h"

UENUM(BlueprintType)
enum class FControllingDeviceType : uint8
{
	CD_Mouse 	UMETA(DisplayName = "Mouse"),
	CD_Touch 	UMETA(DisplayName = "Touch"),
	CD_Gyro 	UMETA(DisplayName = "Gyro"),
};

/**
 * 
 */
UCLASS()
class SHOOTER_API AGameplayPlayerController : public APlayerController
{
	GENERATED_BODY()


	// Store the widget
	class UUserWidget* DebugSensitivityMenu;

public:



	AGameplayPlayerController();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TAssetSubclassOf<class UUserWidget> wDebugSensitivity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
	FControllingDeviceType ControllingDevice;

/*CONTROLS*/

/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// Mouse

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float MouseSensitivityMin;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float MouseSensitivityMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float CurrentMouseSensitivity;

	// Touch

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float TouchSensitivityMin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float TouchSensitivityMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float CurrentTouchSensitivity;

	// Gyro

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float GyroSensitivityMin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float GyroSensitivityMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controls)
		float CurrentGyroSensitivity;
	

	////////////////////////////////////////////////////////////////////
public:
	virtual void SetupInputComponent() override;

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};

	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	void HandleTilt(const FVector Val);
	TouchData	TouchItem;
	FVector LastTilt;

	UFUNCTION(BlueprintCallable)
	void ToggleSensitivityMenu();

	bool bSensitivityMenuActive;

	virtual void AddPitchInput(float Val) override;

	virtual void AddYawInput(float Val) override;

	UFUNCTION(BlueprintPure, Category = Controls)
	FControllingDeviceType GetControllingDevice() {
		return this->ControllingDevice;	};

	UFUNCTION(BlueprintCallable)
	void SetControllingDevice(const FControllingDeviceType Device) {
		ControllingDevice = Device; };

	UFUNCTION(BlueprintCallable)
	float GetSensitivity(FControllingDeviceType Device, bool isCurrentDevice);

	UFUNCTION(BlueprintCallable)
	void SetSensitivity(FControllingDeviceType Device, float NewSensitivity);
};
