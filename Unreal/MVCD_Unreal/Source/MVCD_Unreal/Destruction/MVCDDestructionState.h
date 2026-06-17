#pragma once

#include "CoreMinimal.h"
#include "MVCDDestructionState.generated.h"

UENUM(BlueprintType)
enum class EMVCDDestructionState : uint8
{
	Healthy		UMETA(DisplayName = "Healthy"),
	Damaged		UMETA(DisplayName = "Damaged"),
	Critical	UMETA(DisplayName = "Critical"),
	Destroyed	UMETA(DisplayName = "Destroyed")
};