#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"
class UInputAction;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseButtonPressedSignature);

UCLASS()
class ASSIGNMENT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FPauseButtonPressedSignature PauseButtonPressed;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	APlayerCharacter();
	void PauseActionButtonPressed();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;
};
