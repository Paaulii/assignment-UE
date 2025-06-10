// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "GenericPlatform/ICursor.h"

void UPauseMenuWidget::SetCursor(EMouseCursor::Type CursorType)
{
	OnChangeCursor.Broadcast(CursorType);
}

void UPauseMenuWidget::OnShow()
{
	OnShowScreen.Broadcast();
}

void UPauseMenuWidget::OnHide()
{
	OnHideScreen.Broadcast();
}
