#include "PauseMenuWidget.h"
#include "GenericPlatform/ICursor.h"

void UPauseMenuWidget::SetViewModel(UPauseMenuViewModel* PauseMenuViewModel)
{
	ViewModel = PauseMenuViewModel;
	OnViewModelUpdated.Broadcast(PauseMenuViewModel);
}