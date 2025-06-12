#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Enums.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

float APlayerCharacter::GetMaxHealth()
{
	return MaxHealth;
}

float APlayerCharacter::GetHealth()
{
	return Health;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::PauseActionButtonPressed);
		EnhancedInputComponent->BindAction(ChangeHealthAction, ETriggerEvent::Started, this, &APlayerCharacter::ChangeHealth);
		EnhancedInputComponent->BindAction(LeftSlotActivateAction, ETriggerEvent::Started, this, &APlayerCharacter::HandleLeftSlotActivate);
		EnhancedInputComponent->BindAction(MiddleSlotActivateAction, ETriggerEvent::Started, this, &APlayerCharacter::HandleMiddleSlotActivate);
		EnhancedInputComponent->BindAction(RightSlotActivateAction, ETriggerEvent::Started, this, &APlayerCharacter::HandleRightSlotActivate);
	}
}

void APlayerCharacter::PauseActionButtonPressed()
{
	PauseButtonPressed.Broadcast();
}

void APlayerCharacter::ChangeHealth()
{
	if (Health >= MaxHealth) {
		Health = MaxHealth;
		IncrementMode = EHealthIncrementMode::Decrement;
	}
	else if (Health <= 0) {
		Health = 0;
		IncrementMode = EHealthIncrementMode::Increment;
	}

	Health += IncrementMode == EHealthIncrementMode::Increment?  HealthDecrementValue : -HealthDecrementValue;
	OnHealthChanged.Broadcast(Health);
}

void APlayerCharacter::HandleLeftSlotActivate()
{
	HandleSlotActivation(1);
}

void APlayerCharacter::HandleMiddleSlotActivate()
{
	HandleSlotActivation(2);
}

void APlayerCharacter::HandleRightSlotActivate()
{
	HandleSlotActivation(3);
}

void APlayerCharacter::HandleSlotActivation(int8 SlotNumber)
{
	Energy = EnergyIncrementValue * SlotNumber;
	OnEnergyChanged.Broadcast(Energy);
}
