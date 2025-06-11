#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "HUDViewModel.generated.h"
class APlayerCharacter;

UCLASS()
class ASSIGNMENT_API UHUDViewModel : public UViewModelBase
{
	GENERATED_BODY()
public: 
	void SetModel(APlayerCharacter* PlayerCharacter) override;
};
