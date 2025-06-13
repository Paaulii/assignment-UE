#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"
class UInputAction;
enum class EHealthIncrementMode : uint8;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseButtonPressedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSig, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnergyChangedSig, float, Value);

UCLASS()
class ASSIGNMENT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetHealth() const
	{
		return Health;
	}

	float GetEnergy() const
	{
		return Energy;
	}

	float GetMaxHealth() const
	{
		return MaxHealth;
	}

	float GetMaxEnergy() const
	{
		return MaxEnergy;
	}

	float GetEnergyIncrementValue() const
	{
		return EnergyIncrementValue;
	}

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSig OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnEnergyChangedSig OnEnergyChanged;

	UPROPERTY(BlueprintAssignable)
	FPauseButtonPressedSignature PauseButtonPressed;

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadOnly)
	float Energy = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float Health = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxEnergy = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float HealthIncrementValue = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	uint8 SlotsCount = 0;

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

private:
	void PauseActionButtonPressed();
	void HandleLeftSlotActivation();
	void HandleMiddleSlotActivation();
	void HandleRightSlotActivation();
	void ChangeHealth();
	void HandleSlotActivation(int8 SlotNumber);

	float EnergyIncrementValue = 0.0f;
	EHealthIncrementMode IncrementMode;
};
