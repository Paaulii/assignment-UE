#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "PauseMenuViewModel.generated.h"
class AAssigmentPlayerController;
enum class EHardwareDevicePrimaryType : uint8;
enum EMouseCursor::Type : int;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowViewSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideViewSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCursorSig, EMouseCursor::Type, CursorType);

UCLASS()
class ASSIGNMENT_API UPauseMenuViewModel : public UViewModelBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FOnChangeCursorSig OnChangeCursor;

	UPROPERTY(BlueprintAssignable)
	FOnShowViewSig OnShowView;

	UPROPERTY(BlueprintAssignable)
	FOnHideViewSig OnHideView;

	UFUNCTION(BlueprintCallable)
	void SetHidePauseMenuTimeout(float Timeout);

	UFUNCTION(BlueprintCallable)
	void QuitGame();

	UFUNCTION(BlueprintCallable)
	void ReturnToGame();

	void SetModels(APlayerCharacter* PlayerCharacter, AAssigmentPlayerController* Controller);
private:
	uint8 bPauseMenuActive : 1;

	uint8 bHidePauseMenuTimerSet : 1;

	float HidePauseMenuTimeout;

	FTimerHandle HideTimer;

	AAssigmentPlayerController* PlayerController;


	FInputModeGameAndUI InputMode;

	UInputDeviceSubsystem* InputDeviceSubsystem;

	UFUNCTION()
	void TogglePauseMenu();

	void AdjustViewportPerPlatform();
	void HidePauseMenu();
	EHardwareDevicePrimaryType GetPlayerRecentlyUsedDeviceType() const;
};
