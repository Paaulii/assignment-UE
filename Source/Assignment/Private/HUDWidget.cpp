// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "HUDViewModel.h"

void UHUDWidget::SetViewModel(UHUDViewModel* HUDViewModel)
{
	OnViewModelUpdated.Broadcast(HUDViewModel);
}
