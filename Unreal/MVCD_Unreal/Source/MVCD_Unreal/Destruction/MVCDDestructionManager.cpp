// Fill out your copyright notice in the Description page of Project Settings.

#include "EngineUtils.h"
#include "Destruction/MVCDDestructionManager.h"

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

	if (RegisteredDestructibleActors.Num() > 0)
	{
		FMVCDDestructionEvent TestEvent;

		TestEvent.DamageAmount = 50.0f;
		TestEvent.TargetActor = RegisteredDestructibleActors[0];

		ProcessDestructionEvent(TestEvent);
	}
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

		UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: Registered actor %s"),
			*DestructibleActor->GetName());
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

	DestructionComponent->ApplyDamage(DestructionEvent);

	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Manager: Processed destruction event for %s"),
		*DestructionEvent.TargetActor->GetName());
}
