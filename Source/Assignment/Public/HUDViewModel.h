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

	void SetModel(APlayerCharacter* PlayerCharacter) override;
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Category = "ViewModel")
	float ProgressFillPercentage;

	UPROPERTY(BlueprintReadOnly, FieldNotify,Setter, Category = "ViewModel")
	float Health;
private:
	EHealthState LastHealthState;

	float MaxHealth;

	float LowHealthTreshold;

	UFUNCTION()
	void SetProgressFillPercentage(float Value);

	UFUNCTION()
	void SetHealth(float Value);

	void ChangeHealthState();
};
