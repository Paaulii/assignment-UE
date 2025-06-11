
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"
enum EMouseCursor::Type : int;
class UPauseMenuViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPauseMenuViewModelUpdatedSig, UPauseMenuViewModel*, ViewModel);

UCLASS()
class ASSIGNMENT_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pause Menu Config")
	float HidePauseMenuTimeout;

	UPauseMenuViewModel* ViewModel;

	void SetViewModel(UPauseMenuViewModel* PauseMenuViewModel);
protected:
	UPROPERTY(BlueprintAssignable)
	FOnPauseMenuViewModelUpdatedSig OnViewModelUpdated;

	FTimerHandle HideTimer;
};
