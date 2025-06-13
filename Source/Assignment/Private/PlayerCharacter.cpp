#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Enums.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Health = MaxHealth;
	Energy = 0;
	EnergyIncrementValue = MaxEnergy / SlotsCount;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::PauseActionButtonPressed);
		EnhancedInputComponent->BindAction(ChangeHealthAction, ETriggerEvent::Started, this, &APlayerCharacter::ChangeHealth);
		EnhancedInputComponent->BindAction(LeftSlotActivateAction, ETriggerEvent::Started, this, &APlayerCharacter::HandleLeftSlotActivation);
		EnhancedInputComponent->BindAction(MiddleSlotActivateAction, ETriggerEvent::Started, this, &APlayerCharacter::HandleMiddleSlotActivation);
		EnhancedInputComponent->BindAction(RightSlotActivateAction, ETriggerEvent::Started, this, &APlayerCharacter::HandleRightSlotActivation);
	}
}

void APlayerCharacter::PauseActionButtonPressed()
{
	PauseButtonPressed.Broadcast();
}

void APlayerCharacter::ChangeHealth()
{
	if (Health >= MaxHealth) 
	{
		Health = MaxHealth;
		IncrementMode = EHealthIncrementMode::Decrement;
	}
	else if (Health <= 0) 
	{
		Health = 0;
		IncrementMode = EHealthIncrementMode::Increment;
	}

	Health += IncrementMode == EHealthIncrementMode::Increment?  HealthIncrementValue : -HealthIncrementValue;
	OnHealthChanged.Broadcast(Health);
}

void APlayerCharacter::HandleLeftSlotActivation()
{
	HandleSlotActivation(1);
}

void APlayerCharacter::HandleMiddleSlotActivation()
{
	HandleSlotActivation(2);
}

void APlayerCharacter::HandleRightSlotActivation()
{
	HandleSlotActivation(3);
}

void APlayerCharacter::HandleSlotActivation(int8 SlotNumber)
{
	Energy = EnergyIncrementValue * SlotNumber;
	OnEnergyChanged.Broadcast(Energy);
}
