#include "PauseMenuViewModel.h"
#include "PlayerCharacter.h"
#include "AssigmentPlayerController.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputDeviceProperties.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenuViewModel::SetModels(APlayerCharacter* PlayerCharacter, AAssigmentPlayerController* Controller)
{
	Super::SetModel(PlayerCharacter);
	PlayerController = Controller;
	bPauseMenuActive = false;
	bHidePauseMenuTimerSet = false;

	Model->PauseButtonPressed.AddDynamic(this, &UPauseMenuViewModel::TogglePauseMenu);
	InputDeviceSubsystem = UInputDeviceSubsystem::Get();
}

void UPauseMenuViewModel::TogglePauseMenu()
{
	if (bHidePauseMenuTimerSet) {
		return;
	}

	bPauseMenuActive = !bPauseMenuActive;
	if (bPauseMenuActive) {
		PlayerController->SetPauseMenuVisible(true);
		AdjustViewportPerPlatform();
		OnShowView.Broadcast();
	}
	else {
		bHidePauseMenuTimerSet = true;
		OnHideView.Broadcast();
		PlayerController->GetWorldTimerManager().SetTimer(HideTimer, this, &UPauseMenuViewModel::HidePauseMenu, HidePauseMenuTimeout, false);
	}
}

void UPauseMenuViewModel::AdjustViewportPerPlatform()
{
	EHardwareDevicePrimaryType LastUsedDevice = GetPlayerRecentlyUsedDeviceType();
	EMouseCursor::Type CursorType = LastUsedDevice == EHardwareDevicePrimaryType::KeyboardAndMouse ?
		EMouseCursor::Type::Default : EMouseCursor::Type::None;
	OnChangeCursor.Broadcast(CursorType);
}

void UPauseMenuViewModel::HidePauseMenu()
{
	PlayerController->SetPauseMenuVisible(false);
	bHidePauseMenuTimerSet = false;
	OnViewHidden.Broadcast();
}

void UPauseMenuViewModel::SetHidePauseMenuTimeout(float Timeout)
{
	HidePauseMenuTimeout = Timeout;
}

void UPauseMenuViewModel::QuitGame()
{
	PlayerController->QuitGame();
}

void UPauseMenuViewModel::ReturnToGame()
{
	TogglePauseMenu();
}

EHardwareDevicePrimaryType UPauseMenuViewModel::GetPlayerRecentlyUsedDeviceType() const
{
	if (InputDeviceSubsystem != nullptr && PlayerController)
	{
		FHardwareDeviceIdentifier HardwareDevice = InputDeviceSubsystem->GetMostRecentlyUsedHardwareDevice(PlayerController->GetPlatformUserId());
		return HardwareDevice.PrimaryDeviceType;
	}

	return EHardwareDevicePrimaryType::Unspecified;
}