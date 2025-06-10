// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"
class UHUDViewModel;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnViewModelUpdatedSignature, UHUDViewModel*, ViewModel);

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetViewModel(UHUDViewModel* HUDViewModel);
protected:
	UPROPERTY(BlueprintAssignable)
	FOnViewModelUpdatedSignature OnViewModelUpdated;
};
