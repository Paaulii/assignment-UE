#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ViewModelBase.generated.h"
class APlayerCharacter;

UCLASS()
class ASSIGNMENT_API UViewModelBase : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	virtual void SetModel(APlayerCharacter* PlayerCharacter);
protected:
	APlayerCharacter* Model;
};
