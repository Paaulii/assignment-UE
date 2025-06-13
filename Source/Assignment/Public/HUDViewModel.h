#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "Enums.h"
#include "HUDViewModel.generated.h"
class APlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeHealthState, EHealthState, LastHealthState, EHealthState, NewHealthState);
UCLASS()
class ASSIGNMENT_API UHUDViewModel : public UViewModelBase
{
	GENERATED_BODY()
public: 
	void SetModel(APlayerCharacter* PlayerCharacter) override;

	UPROPERTY(BlueprintAssignable)
	FOnChangeHealthState OnChangeHealthState;
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Category = "ViewModel")
	float ProgressFillPercentage;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Category = "ViewModel")
	float EnergyFillPercentage;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Category = "ViewModel")
	uint8 ActiveSlotsNumber;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Category = "ViewModel")
	float Health;

	UPROPERTY(EditDefaultsOnly)
	float LowHealthPercentageThreshold;
private:
	UFUNCTION()
	void SetProgressFillPercentage(float Value);

	UFUNCTION()
	void SetEnergyFillPercentage(float Value);

	UFUNCTION()
	void SetActiveSlotsNumber(uint8 Value);

	UFUNCTION()
	void SetHealth(float Value);

	void ChangeHealthState();

	float MaxHealth;
	float LowHealthTreshold;
	float MaxEnergy;
	EHealthState LastHealthState = EHealthState::Default;
	uint8 EnergyIncrementValue;
};
