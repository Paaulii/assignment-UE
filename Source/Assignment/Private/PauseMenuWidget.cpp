#include "PauseMenuWidget.h"

void UPauseMenuWidget::SetViewModel(UPauseMenuViewModel* PauseMenuViewModel)
{
	ViewModel = PauseMenuViewModel;
	OnViewModelUpdated.Broadcast(PauseMenuViewModel);
}