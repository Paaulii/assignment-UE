#include "AssigmentPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "HUDViewModel.h"
#include "PauseMenuWidget.h"
#include "HUDWidget.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputDeviceProperties.h"

void AAssigmentPlayerController::BeginPlay()
{
	bPauseMenuActive = false;
	bHidePauseMenuTimerSet = false;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());

	if (PlayerCharacter != nullptr) {

		PlayerCharacter->PauseButtonPressed.AddDynamic(this, &AAssigmentPlayerController::TogglePauseMenu);
		SetupUI();
	}

	InputDeviceSubsystem = UInputDeviceSubsystem::Get();
	InputDeviceSubsystem->OnInputHardwareDeviceChanged.AddDynamic( this, &AAssigmentPlayerController::HandleHardwareDeviceChanged);
}

void AAssigmentPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	PlayerCharacter->PauseButtonPressed.RemoveDynamic(this, &AAssigmentPlayerController::TogglePauseMenu);
	PauseMenuWidget->RemoveFromParent();
	HudWidget->RemoveFromParent();
}

void AAssigmentPlayerController::TogglePauseMenu()
{
	if (bHidePauseMenuTimerSet) {
		return;
	}

	bPauseMenuActive = !bPauseMenuActive;
	if (bPauseMenuActive) {
		PauseMenuWidget->AddToViewport();
		SetInputMode(FInputModeGameAndUI());
		AdjustViewportPerPlatform();
		PauseMenuWidget->OnShow();
	}
	else {
		bHidePauseMenuTimerSet = true;
		PauseMenuWidget->OnHide();
		GetWorldTimerManager().SetTimer(HideTimer, this, &AAssigmentPlayerController::HidePauseMenu, HidePauseMenuTimeout, false);
	}
}

void AAssigmentPlayerController::SetupUI()
{
	HudViewModel = NewObject<UHUDViewModel>();
	HudViewModel->SetModel(PlayerCharacter);

	PauseMenuWidget = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);
	HudWidget = CreateWidget<UHUDWidget>(GetWorld(), HudWidgetClass);

	if (HudWidget != nullptr && HudViewModel != nullptr) {
		HudWidget->SetViewModel(HudViewModel);
		HudWidget->AddToViewport();
	}
}

void AAssigmentPlayerController::AdjustViewportPerPlatform()
{
	EHardwareDevicePrimaryType LastUsedDevice = GetPlayerRecentlyUsedDeviceType();
	EMouseCursor::Type CursorType = LastUsedDevice == EHardwareDevicePrimaryType::KeyboardAndMouse? 
		EMouseCursor::Type::Default : EMouseCursor::Type::None;
	PauseMenuWidget->SetCursor(CursorType);
}

void AAssigmentPlayerController::HandleHardwareDeviceChanged(const FPlatformUserId UserId, const FInputDeviceId DeviceId)
{
	//AdjustViewportPerPlatform();
}

void AAssigmentPlayerController::HidePauseMenu()
{
	PauseMenuWidget->RemoveFromParent();
	SetInputMode(FInputModeGameOnly());
	bHidePauseMenuTimerSet = false;
}

EHardwareDevicePrimaryType AAssigmentPlayerController::GetPlayerRecentlyUsedDeviceType() const
{
	if (InputDeviceSubsystem != nullptr)
	{
		FHardwareDeviceIdentifier HardwareDevice = InputDeviceSubsystem->GetMostRecentlyUsedHardwareDevice(GetPlatformUserId());
		UE_LOG(LogTemp, Warning, TEXT("%d"), HardwareDevice.PrimaryDeviceType)
		return HardwareDevice.PrimaryDeviceType;
	}

	return EHardwareDevicePrimaryType::Unspecified;
}
