#include "Destruction/MVCDDestructionReactionComponent.h"
#include "Destruction/MVCDDestructionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

UMVCDDestructionReactionComponent::UMVCDDestructionReactionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMVCDDestructionReactionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	DestructionComponent = Owner->FindComponentByClass<UMVCDDestructionComponent>();

	if (!IsValid(DestructionComponent))
	{
		UE_LOG(LogTemp, Warning,
			TEXT("MVCD Reaction Component: No destruction component found on %s"),
			*Owner->GetName());
		return;
	}

	MeshComponent = Owner->FindComponentByClass<UStaticMeshComponent>();

	if (!IsValid(MeshComponent))
	{
		UE_LOG(LogTemp, Warning,
			TEXT("MVCD Reaction Component: No Static Mesh found on %s"),
			*Owner->GetName());
	}

	DestructionComponent->OnStateChanged.AddDynamic(
		this,
		&UMVCDDestructionReactionComponent::OnDestructionStateChanged
	);

	UE_LOG(LogTemp, Warning,
		TEXT("MVCD Reaction Component: Subscribed to destruction state changes on %s"),
		*Owner->GetName());
}

void UMVCDDestructionReactionComponent::OnDestructionStateChanged(
	EMVCDDestructionState PreviousState,
	EMVCDDestructionState NewState
)
{
	switch (NewState)
	{
	case EMVCDDestructionState::Damaged:

		ApplyDamagedVisuals();

		UE_LOG(LogTemp, Warning,
			TEXT("MVCD Reaction: Object Damaged"));
		break;

	case EMVCDDestructionState::Critical:

		ApplyCriticalVisuals();

		UE_LOG(LogTemp, Warning,
			TEXT("MVCD Reaction: Object Critical"));
		break;

	case EMVCDDestructionState::Destroyed:

		ApplyDestroyedVisuals();

		UE_LOG(LogTemp, Warning,
			TEXT("MVCD Reaction: Object Destroyed"));
		break;

	default:
		break;
	}
}

void UMVCDDestructionReactionComponent::ApplyDamagedVisuals()
{
	if (!IsValid(MeshComponent) || !IsValid(DamagedMaterial))
	{
		return;
	}

	MeshComponent->SetMaterial(0, DamagedMaterial);
}

void UMVCDDestructionReactionComponent::ApplyCriticalVisuals()
{
	if (!IsValid(MeshComponent) || !IsValid(CriticalMaterial))
	{
		return;
	}

	MeshComponent->SetMaterial(0, CriticalMaterial);
}

void UMVCDDestructionReactionComponent::ApplyDestroyedVisuals()
{
	if (!IsValid(MeshComponent) || !IsValid(DestroyedMaterial))
	{
		return;
	}

	MeshComponent->SetMaterial(0, DestroyedMaterial);
}
