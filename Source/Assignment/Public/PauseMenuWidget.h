
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"
enum EMouseCursor::Type : int;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCursorSig, EMouseCursor::Type, CursorType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideSig);
/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnChangeCursorSig OnChangeCursor;

	UPROPERTY(BlueprintAssignable)
	FOnShowSig OnShowScreen;

	UPROPERTY(BlueprintAssignable)
	FOnHideSig OnHideScreen;

	void SetCursor(EMouseCursor::Type CursorType);

	void OnShow();
	void OnHide();
};
