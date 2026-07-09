// Fill out your copyright notice in the Description page of Project Settings.

#include "Destruction/MVCDDestructionManager.h"
#include "TimerManager.h"
#include "EngineUtils.h"

// Sets default values
AMVCDDestructionManager::AMVCDDestructionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMVCDDestructionManager::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("MVCD Destruction Manager: Benchmark disabled on non-authority instance"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: BeginPlay"));

	// rest of your current code...
}

// Called every frame
void AMVCDDestructionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMVCDDestructionManager::RegisterDestructibleActor(AActor* DestructibleActor)
{
	if (!IsValid(DestructibleActor))
	{
		return;
	}

	if (!RegisteredDestructibleActors.Contains(DestructibleActor))
	{
		RegisteredDestructibleActors.Add(DestructibleActor);

	}
}

void AMVCDDestructionManager::UnregisterDestructibleActor(AActor* DestructibleActor)
{
	if (!IsValid(DestructibleActor))
	{
		return;
	}

	RegisteredDestructibleActors.Remove(DestructibleActor);

	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: Unregistered actor %s"),
		*DestructibleActor->GetName());
}

void AMVCDDestructionManager::ProcessDestructionEvent(const FMVCDDestructionEvent& DestructionEvent)
{
	if (!IsValid(DestructionEvent.TargetActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: Invalid target actor"));
		return;
	}

	UMVCDDestructionComponent* DestructionComponent =
		DestructionEvent.TargetActor->FindComponentByClass<UMVCDDestructionComponent>();

	if (!IsValid(DestructionComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: Target has no destruction component"));
		return;
	}

	RegisterDamageEvent();

	DestructionComponent->ApplyDamage(DestructionEvent);

	switch (DestructionComponent->GetCurrentState())
	{
	case EMVCDDestructionState::Destroyed:
		RegisterStateChange();
		RegisterDestroyedObject();
		break;

	case EMVCDDestructionState::Damaged:
		RegisterStateChange();
		RegisterDamagedObject();
		break;

	case EMVCDDestructionState::Critical:
		RegisterStateChange();
		RegisterCriticalObject();
		break;

	default:
		break;
	}

	UE_LOG(LogTemp, Warning,
		TEXT("MVCD Metrics | Damage Events: %d | State Changes: %d | Destroyed: %d | Damaged: %d | Critical: %d"),
		Metrics.TotalDamageEvents,
		Metrics.TotalStateChanges,
		Metrics.TotalDestroyedObjects,
		Metrics.TotalDamagedObjects,
		Metrics.TotalCriticalObjects);

	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: Processed destruction event for %s"),
		*DestructionEvent.TargetActor->GetName());
}

void AMVCDDestructionManager::RunTestDestructionEvent()
{
	if (RegisteredDestructibleActors.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: No registered destructible actors available for test event."));
		return;
	}

	for (AActor* TargetActor : RegisteredDestructibleActors)
	{
		if (!IsValid(TargetActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: Invalid target actor for test event."));
			continue;
		}

		FMVCDDestructionEvent TestEvent;
		TestEvent.DamageAmount = BenchmarkConfig.DamageAmount;
		TestEvent.TargetActor = TargetActor;
		TestEvent.SourceActor = this;
		TestEvent.ImpactLocation = TargetActor->GetActorLocation();
		TestEvent.ImpactDirection = FVector::DownVector;

		UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: Running test destruction event on %s"),
			*TargetActor->GetName());

		ProcessDestructionEvent(TestEvent);
	}
}

void AMVCDDestructionManager::RegisterDamageEvent()
{
	Metrics.TotalDamageEvents++;
}

void AMVCDDestructionManager::RegisterStateChange()
{
	Metrics.TotalStateChanges++;
}

void AMVCDDestructionManager::RegisterDestroyedObject()
{
	Metrics.TotalDestroyedObjects++;
}

void AMVCDDestructionManager::RegisterDamagedObject()
{
	Metrics.TotalDamagedObjects++;
}

void AMVCDDestructionManager::RegisterCriticalObject()
{
	Metrics.TotalCriticalObjects++;
}
void AMVCDDestructionManager::PrintMetricsReport() const
{
	UE_LOG(LogTemp, Warning, TEXT("========== MVCD METRICS REPORT =========="));

	UE_LOG(LogTemp, Warning, TEXT("Total Damage Events: %d"), Metrics.TotalDamageEvents);
	UE_LOG(LogTemp, Warning, TEXT("Total State Changes: %d"), Metrics.TotalStateChanges);
	UE_LOG(LogTemp, Warning, TEXT("Destroyed Objects: %d"), Metrics.TotalDestroyedObjects);
	UE_LOG(LogTemp, Warning, TEXT("Damaged Objects: %d"), Metrics.TotalDamagedObjects);
	UE_LOG(LogTemp, Warning, TEXT("Critical Objects: %d"), Metrics.TotalCriticalObjects);

	UE_LOG(LogTemp, Warning, TEXT("========================================="));
}
void AMVCDDestructionManager::ResetMetrics()
{
	Metrics = FMVCDDestructionMetrics();
}
void AMVCDDestructionManager::RunBenchmark()
{
	if (BenchmarkConfig.bResetMetricsBeforeRun)
	{
		ResetMetrics();
	}

	CurrentBenchmarkIndex = 0;

	if (BenchmarkConfig.DelayBetweenTests <= 0.0f)
	{
		RunTestDestructionEvent();

		if (BenchmarkConfig.bPrintResultsAtEnd)
		{
			PrintMetricsReport();
		}

		return;
	}

	RunBenchmarkStep();
}
void AMVCDDestructionManager::RunBenchmarkStep()
{
	if (!RegisteredDestructibleActors.IsValidIndex(CurrentBenchmarkIndex))
	{
		if (BenchmarkConfig.bPrintResultsAtEnd)
		{
			PrintMetricsReport();
		}

		return;
	}

	AActor* TargetActor = RegisteredDestructibleActors[CurrentBenchmarkIndex];

	if (IsValid(TargetActor))
	{
		FMVCDDestructionEvent TestEvent;
		TestEvent.DamageAmount = BenchmarkConfig.DamageAmount;
		TestEvent.TargetActor = TargetActor;
		TestEvent.SourceActor = this;
		TestEvent.ImpactLocation = TargetActor->GetActorLocation();
		TestEvent.ImpactDirection = FVector::DownVector;

		UE_LOG(LogTemp, Warning,
			TEXT("MVCD Benchmark Step %d/%d on %s"),
			CurrentBenchmarkIndex + 1,
			RegisteredDestructibleActors.Num(),
			*TargetActor->GetName());

		ProcessDestructionEvent(TestEvent);
	}

	CurrentBenchmarkIndex++;

	GetWorldTimerManager().SetTimerForNextTick([this]()
		{
			FTimerHandle TimerHandle;

			GetWorldTimerManager().SetTimer(
				TimerHandle,
				this,
				&AMVCDDestructionManager::RunBenchmarkStep,
				BenchmarkConfig.DelayBetweenTests,
				false
			);
		});
}