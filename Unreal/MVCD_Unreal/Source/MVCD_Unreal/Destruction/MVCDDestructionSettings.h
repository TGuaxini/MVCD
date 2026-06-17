#pragma once

#include "CoreMinimal.h"
#include "MVCDDestructionSettings.generated.h"

USTRUCT(BlueprintType)
struct FMVCDDestructionSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	float MaxIntegrity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	float DestructionThreshold = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	float ImpulseStrength = 250000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	bool bCanBeDestroyed = true;
};