#pragma once

#include "CoreMinimal.h"
#include "MVCDBenchmarkConfig.generated.h"

USTRUCT(BlueprintType)
struct FMVCDBenchmarkConfig
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Benchmark")
    float DamageAmount = 150.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Benchmark")
    float DelayBetweenTests = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Benchmark")
    bool bResetMetricsBeforeRun = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Benchmark")
    bool bPrintResultsAtEnd = true;
};