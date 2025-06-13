#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"


UENUM(BlueprintType)
enum class EHealthState : uint8
{
    Default UMETA(DisplayName = "Default"),
    LowHealth UMETA(DisplayName = "LowHealth"),
    Dead UMETA(DisplayName = "Dead")
};

enum class EHealthIncrementMode : uint8
{
    Increment,
    Decrement
};