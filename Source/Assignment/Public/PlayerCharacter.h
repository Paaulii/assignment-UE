#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"
class UInputAction;
enum class EHealthIncrementMode: uint8;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseButtonPressedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSig, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnergyChangedSig, float, Value);

UCLASS()
class ASSIGNMENT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSig OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnEnergyChangedSig OnEnergyChanged;

	UPROPERTY(BlueprintAssignable)
	FPauseButtonPressedSignature PauseButtonPressed;

	APlayerCharacter();
	float GetMaxHealth();
	float GetHealth();
	float GetEnergy();
	float GetMaxEnergy();
	float GetEnergyIncrementValue();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Energy;

	UPROPERTY(EditDefaultsOnly)
	float MaxEnergy;

	UPROPERTY(EditDefaultsOnly)
	float SlotsCount;

	UPROPERTY(EditDefaultsOnly)
	float HealthIncrementValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* PauseAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ChangeHealthAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* LeftSlotActivateAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MiddleSlotActivateAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* RightSlotActivateAction;

	virtual void PostInitializeComponents() override;
private:
	float EnergyIncrementValue;
	EHealthIncrementMode IncrementMode;
	void PauseActionButtonPressed();
	void ChangeHealth();
	void HandleLeftSlotActivate();
	void HandleMiddleSlotActivate();
	void HandleRightSlotActivate();
	void HandleSlotActivation(int8 SlotNumber);
};
