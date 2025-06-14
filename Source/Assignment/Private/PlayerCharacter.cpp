#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Health = MaxHealth;
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
	OnPauseButtonPressed.Broadcast();
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
	OnSlotPressed.Broadcast(ESlotType::Left);
}

void APlayerCharacter::HandleMiddleSlotActivation()
{
	OnSlotPressed.Broadcast(ESlotType::Middle);
}

void APlayerCharacter::HandleRightSlotActivation()
{
	OnSlotPressed.Broadcast(ESlotType::Right);
}