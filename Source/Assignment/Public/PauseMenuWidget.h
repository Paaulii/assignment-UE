
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"
enum EMouseCursor::Type : int;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCursor, EMouseCursor::Type, CursorType);
/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnChangeCursor OnChangeCursor;

	void SetCursor(EMouseCursor::Type CursorType);

};
