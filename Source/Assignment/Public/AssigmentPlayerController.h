
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AssigmentPlayerController.generated.h"
class UInputMappingContext;
class UPauseMenuWidget;
class UPauseMenuViewModel;
class UWidget;
class UHUDWidget;
class UHUDViewModel;
class APlayerCharacter;
enum class EHardwareDevicePrimaryType : uint8;
enum class ESPMode : uint8;

UCLASS()
class ASSIGNMENT_API AAssigmentPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetGamePaused(bool bIsPaused);
	void SetPauseMenuVisible(bool bIsVisible);
	void QuitGame();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Widget")
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Widget")
	TSubclassOf<UHUDWidget> HudWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Viewmodels")
	TSubclassOf<UHUDViewModel> HudViewModelClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Viewmodels")
	TSubclassOf<UPauseMenuViewModel> PauseMenuViewModelClass;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;
private:
	void SetupUI();

	UPROPERTY()
	TObjectPtr<UPauseMenuWidget> PauseMenuWidget;

	UPROPERTY()
	TObjectPtr<UHUDWidget> HudWidget;

	APlayerCharacter* PlayerCharacter;
	UHUDViewModel* HudViewModel;
	UPauseMenuViewModel* PauseMenuViewModel;
};
