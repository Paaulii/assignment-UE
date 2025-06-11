
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
	void SetPauseMenuVisible(bool bIsVisible);
	void QuitGame();
protected:
	UPROPERTY(EditAnywhere, Category = "Widget Class")
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widget Class")
	TSubclassOf<UHUDWidget> HudWidgetClass;

	virtual void BeginPlay() override;
private:
	APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	TObjectPtr<UPauseMenuWidget> PauseMenuWidget;

	UPROPERTY()
	TObjectPtr<UHUDWidget> HudWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UHUDViewModel* HudViewModel;
	UPauseMenuViewModel* PauseMenuViewModel;

	void SetupUI();
};
