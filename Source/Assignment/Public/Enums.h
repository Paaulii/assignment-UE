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

UENUM(BlueprintType)
enum class EHealthIncrementMode : uint8
{
    Increment,
    Decrement
};

UENUM(BlueprintType)
enum class ESlotType : uint8
{
    Left,
    Middle,
    Right
};
