#include "HUDViewModel.h"
#include "PlayerCharacter.h"
#include "Enums.h"

void UHUDViewModel::SetModel(APlayerCharacter* PlayerCharacter)
{
	Super::SetModel(PlayerCharacter);

	Model->OnHealthChanged.AddDynamic(this, &UHUDViewModel::SetProgressFillPercentage);
	MaxHealth = Model->GetMaxHealth();
	LowHealthTreshold = MaxHealth * 0.25f;
	SetProgressFillPercentage(Model->GetHealth());
	LastHealthState = EHealthState::Default;
}

void UHUDViewModel::SetProgressFillPercentage(float Value)
{
	float Percentage = Value / MaxHealth;
	if (UE_MVVM_SET_PROPERTY_VALUE(ProgressFillPercentage, Percentage))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ProgressFillPercentage);
		SetHealth(Value);
		ChangeHealthState();
	}
}

void UHUDViewModel::SetHealth(float Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Health, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Health);
	}
}

void UHUDViewModel::ChangeHealthState()
{
	EHealthState HealthState = EHealthState::Default;

	if (Health <= LowHealthTreshold) {
		HealthState = EHealthState::LowHealth;
	}

	if (Health == 0) {
		HealthState = EHealthState::Dead;
	}

	if (LastHealthState != HealthState) {
		OnChangeHealthState.Broadcast(LastHealthState, HealthState);
		LastHealthState = HealthState;
	}
}
