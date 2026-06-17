#pragma once

#include "CoreMinimal.h"
#include "MVCDDestructionMetrics.generated.h"

USTRUCT(BlueprintType)
struct FMVCDDestructionMetrics
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalDamageEvents = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalStateChanges = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalDestroyedObjects = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalDamagedObjects = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalCriticalObjects = 0;
};