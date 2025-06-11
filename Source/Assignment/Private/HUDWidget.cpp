#include "HUDWidget.h"
#include "HUDViewModel.h"

void UHUDWidget::SetViewModel(UHUDViewModel* HUDViewModel)
{
	OnViewModelUpdated.Broadcast(HUDViewModel);
}
