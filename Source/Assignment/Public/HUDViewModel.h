#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "HUDViewModel.generated.h"
class APlayerCharacter;
enum class EHealthState: uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeHealthState, EHealthState, LastHealthState, EHealthState, NewHealthState);
UCLASS()
class ASSIGNMENT_API UHUDViewModel : public UViewModelBase
{
	GENERATED_BODY()
public: 
	UPROPERTY(BlueprintAssignable)
	FOnChangeHealthState OnChangeHealthState;

	UFUNCTION()
	float GetProgressFillPercentage() const;

	void SetModel(APlayerCharacter* PlayerCharacter) override;
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, Category = "ViewModel")
	float ProgressFillPercentage;

private:
	EHealthState LastHealthState;

	float MaxHealth;

	float LowHealthTreshold;

	UFUNCTION()
	void SetProgressFillPercentage(float Value);

	void ChangeHealthState(float Health);
};
