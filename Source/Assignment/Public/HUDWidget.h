
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"
class UHUDViewModel;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDViewModelUpdatedSig, UHUDViewModel*, ViewModel);

UCLASS()
class ASSIGNMENT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetViewModel(UHUDViewModel* HUDViewModel);
protected:
	UPROPERTY(BlueprintAssignable)
	FOnHUDViewModelUpdatedSig OnViewModelUpdated;
};
