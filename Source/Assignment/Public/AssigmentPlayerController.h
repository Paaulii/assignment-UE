// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AssigmentPlayerController.generated.h"
class UInputMappingContext;
class UPauseMenuWidget;
class UWidget;
class UHUDWidget;
class UHUDViewModel;
class APlayerCharacter;
enum class EHardwareDevicePrimaryType : uint8;
enum class ESPMode : uint8;
/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AAssigmentPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Pause Menu Config")
	float HidePauseMenuTimeout;

	UPROPERTY(EditAnywhere, Category = "Widget Class")
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widget Class")
	TSubclassOf<UHUDWidget> HudWidgetClass;

	FTimerHandle HideTimer;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	uint8 bPauseMenuActive : 1;

	uint8 bHidePauseMenuTimerSet:1;

	FInputModeGameAndUI InputMode;

	UInputDeviceSubsystem* InputDeviceSubsystem;

	APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	TObjectPtr<UPauseMenuWidget> PauseMenuWidget;

	UPROPERTY()
	TObjectPtr<UHUDWidget> HudWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UHUDViewModel* HudViewModel;

	UFUNCTION()
	void TogglePauseMenu();


	UFUNCTION()
	void HandleHardwareDeviceChanged(const FPlatformUserId UserId, const FInputDeviceId DeviceId);

	void SetupUI();

	void AdjustViewportPerPlatform();

	void HidePauseMenu();
	EHardwareDevicePrimaryType GetPlayerRecentlyUsedDeviceType() const;
};
