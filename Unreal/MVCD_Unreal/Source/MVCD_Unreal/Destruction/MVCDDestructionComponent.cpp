// Fill out your copyright notice in the Description page of Project Settings.

#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Destruction/MVCDDestructionComponent.h"

// Sets default values for this component's properties
UMVCDDestructionComponent::UMVCDDestructionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMVCDDestructionComponent::BeginPlay()
{
	Super::BeginPlay();

	CacheGeometryCollectionComponent();
	
}


// Called every frame
void UMVCDDestructionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMVCDDestructionComponent::ApplyDamage(const FMVCDDestructionEvent& DestructionEvent)
{
	if (!IsValid(GeometryCollectionComponent))
	{
		CacheGeometryCollectionComponent();
	}

	CurrentIntegrity -= DestructionEvent.DamageAmount;

	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Component: Damage Applied: %f | Current Integrity: %f"),
		DestructionEvent.DamageAmount,
		CurrentIntegrity);

	if (CanBeDestroyed())
	{
		HandleDestruction(DestructionEvent);
	}
}

bool UMVCDDestructionComponent::CanBeDestroyed() const
{
	return CurrentIntegrity <= DestructionThreshold;
}

void UMVCDDestructionComponent::HandleDestruction(const FMVCDDestructionEvent& DestructionEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Component: Destruction Triggered"));

	TriggerDestructionResponse(DestructionEvent);
}

void UMVCDDestructionComponent::CacheGeometryCollectionComponent()
{
	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	GeometryCollectionComponent = Owner->FindComponentByClass<UGeometryCollectionComponent>();

	if (IsValid(GeometryCollectionComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Component: Geometry Collection cached on %s"),
			*Owner->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Component: No Geometry Collection found on %s"),
			*Owner->GetName());
	}
}

void UMVCDDestructionComponent::TriggerDestructionResponse(const FMVCDDestructionEvent& DestructionEvent)
{
	if (!IsValid(GeometryCollectionComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Component: Cannot trigger destruction response. Geometry Collection is invalid."));
		return;
	}

	FVector ImpulseDirection = DestructionEvent.ImpactDirection;

	if (ImpulseDirection.IsNearlyZero())
	{
		ImpulseDirection = FVector::UpVector;
	}

	ImpulseDirection.Normalize();

	const FVector Impulse = ImpulseDirection * DestructionImpulseStrength;

	GeometryCollectionComponent->AddImpulse(Impulse, NAME_None, true);

	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Component: Applied impulse to Geometry Collection. Strength: %f"),
		DestructionImpulseStrength);
}