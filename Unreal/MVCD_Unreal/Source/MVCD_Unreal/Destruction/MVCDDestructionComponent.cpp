// Fill out your copyright notice in the Description page of Project Settings.


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

	// ...
	
}


// Called every frame
void UMVCDDestructionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMVCDDestructionComponent::ApplyDamage(const FMVCDDestructionEvent& DestructionEvent)
{
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
}
