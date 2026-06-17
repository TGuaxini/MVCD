// Fill out your copyright notice in the Description page of Project Settings.

#include "Destruction/MVCDDestructionComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

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

	CurrentIntegrity = Settings.MaxIntegrity;

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

	UpdateDestructionState();

	UE_LOG(LogTemp, Warning,
		TEXT("MVCD Damage Applied | Damage: %.2f | Remaining Integrity: %.2f"),
		DestructionEvent.DamageAmount,
		CurrentIntegrity);

	if (CanBeDestroyed())
	{
		HandleDestruction(DestructionEvent);
	}
}

bool UMVCDDestructionComponent::CanBeDestroyed() const
{
	return Settings.bCanBeDestroyed &&
		CurrentIntegrity <= Settings.DestructionThreshold;
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

	}
	else
	{

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

	const FVector Impulse = ImpulseDirection * Settings.ImpulseStrength;

	GeometryCollectionComponent->AddImpulse(Impulse, NAME_None, true);

	UE_LOG(LogTemp, Warning, TEXT("MVCD Destruction Component: Applied impulse to Geometry Collection. Strength: %f"),
		Settings.ImpulseStrength);
}

void UMVCDDestructionComponent::UpdateDestructionState()
{
	const float IntegrityPercent =
		(CurrentIntegrity / Settings.MaxIntegrity) * 100.0f;

	EMVCDDestructionState PreviousState = CurrentState;

	if (CurrentIntegrity <= Settings.DestructionThreshold)
	{
		CurrentState = EMVCDDestructionState::Destroyed;
	}
	else if (IntegrityPercent <= 25.0f)
	{
		CurrentState = EMVCDDestructionState::Critical;
	}
	else if (IntegrityPercent <= 50.0f)
	{
		CurrentState = EMVCDDestructionState::Damaged;
	}
	else
	{
		CurrentState = EMVCDDestructionState::Healthy;
	}

	if (PreviousState != CurrentState)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("MVCD State Updated | Integrity: %.2f | State: %d"),
			CurrentIntegrity,
			static_cast<int32>(CurrentState));
	}
}