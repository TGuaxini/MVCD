#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MVCDDestructionEvent.generated.h"

USTRUCT(BlueprintType)
struct FMVCDDestructionEvent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	FVector ImpactLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	FVector ImpactDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	float DamageAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	AActor* SourceActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	AActor* TargetActor = nullptr;
};