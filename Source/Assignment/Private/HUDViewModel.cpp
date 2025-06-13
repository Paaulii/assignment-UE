#include "HUDViewModel.h"
#include "PlayerCharacter.h"

void UHUDViewModel::SetModel(APlayerCharacter* PlayerCharacter)
{
	Super::SetModel(PlayerCharacter);

	if (Model == nullptr) 
	{
		return;
	}

	Model->OnHealthChanged.AddDynamic(this, &UHUDViewModel::SetProgressFillPercentage);
	Model->OnEnergyChanged.AddDynamic(this, &UHUDViewModel::SetEnergyFillPercentage);

	MaxHealth = Model->GetMaxHealth();
	LowHealthTreshold = MaxHealth * LowHealthPercentageThreshold;
	SetProgressFillPercentage(Model->GetHealth());

	MaxEnergy = Model->GetMaxEnergy();
	EnergyIncrementValue = Model->GetEnergyIncrementValue();
	SetEnergyFillPercentage(Model->GetEnergy());
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

void UHUDViewModel::SetEnergyFillPercentage(float Value)
{
	float Percentage = Value / MaxEnergy;
	if (UE_MVVM_SET_PROPERTY_VALUE(EnergyFillPercentage, Percentage))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(EnergyFillPercentage);
		SetActiveSlotsNumber(Value);
	}
}

void UHUDViewModel::SetActiveSlotsNumber(uint8 Value)
{
	float SlotsNumber = FMath::Floor(Value / EnergyIncrementValue);
	if (UE_MVVM_SET_PROPERTY_VALUE(ActiveSlotsNumber, SlotsNumber))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ActiveSlotsNumber);
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

	if (Health <= LowHealthTreshold) 
	{
		HealthState = EHealthState::LowHealth;
	}

	if (Health <= 0) 
	{
		HealthState = EHealthState::Dead;
	}

	if (LastHealthState != HealthState) 
	{
		OnChangeHealthState.Broadcast(LastHealthState, HealthState);
		LastHealthState = HealthState;
	}
}
