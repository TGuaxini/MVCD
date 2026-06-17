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

	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: BeginPlay"));

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AActor* Actor = *ActorItr;

		if (Actor->ActorHasTag("Destructible"))
		{
			RegisterDestructibleActor(Actor);
		}
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &AMVCDDestructionManager::RunTestDestructionEvent);
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
		TestEvent.DamageAmount = 150.0f;
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