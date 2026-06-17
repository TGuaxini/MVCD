#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MVCDDestructionState.h"
#include "MVCDDestructionReactionComponent.generated.h"

class UMVCDDestructionComponent;
class UStaticMeshComponent;
class UMaterialInterface;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MVCD_UNREAL_API UMVCDDestructionReactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMVCDDestructionReactionComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UMVCDDestructionComponent* DestructionComponent = nullptr;

	UPROPERTY()
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Visual Feedback")
	UMaterialInterface* DamagedMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Visual Feedback")
	UMaterialInterface* CriticalMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Visual Feedback")
	UMaterialInterface* DestroyedMaterial = nullptr;

	UFUNCTION()
	void OnDestructionStateChanged(
		EMVCDDestructionState PreviousState,
		EMVCDDestructionState NewState
	);

	void ApplyDamagedVisuals();
	void ApplyCriticalVisuals();
	void ApplyDestroyedVisuals();
};