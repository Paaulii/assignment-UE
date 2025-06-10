// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "HUDViewModel.generated.h"
class APlayerCharacter;

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UHUDViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public: 
	void SetModel(APlayerCharacter* PlayerCharacter);

private:
	APlayerCharacter* Model;
};
