// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVCDDestructionSettings.h"
#include "MVCDDestructionState.h"
#include "MVCDDestructionEvent.h"
#include "Components/ActorComponent.h"
#include "MVCDDestructionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMVCDOnStateChanged, EMVCDDestructionState, PreviousState, EMVCDDestructionState, NewState);

class UGeometryCollectionComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MVCD_UNREAL_API UMVCDDestructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMVCDDestructionComponent();

	UPROPERTY(BlueprintAssignable, Category = "MVCD|Destruction")
	FMVCDOnStateChanged OnStateChanged;

	UPROPERTY()
	EMVCDDestructionState PreviousReplicatedState = EMVCDDestructionState::Healthy;

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void ApplyDamage(const FMVCDDestructionEvent& DestructionEvent);

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	bool CanBeDestroyed() const;

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void HandleDestruction(const FMVCDDestructionEvent& DestructionEvent);

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void TriggerDestructionResponse(const FMVCDDestructionEvent& DestructionEvent);

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void UpdateDestructionState();

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	EMVCDDestructionState GetCurrentState() const;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MVCD|Networking")
	void ServerApplyDamage(const FMVCDDestructionEvent& DestructionEvent);


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentIntegrity, VisibleAnywhere, BlueprintReadOnly, Category = "MVCD|Destruction")
	float CurrentIntegrity = 100.0f;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentState, VisibleAnywhere, BlueprintReadOnly, Category = "MVCD|Destruction")
	EMVCDDestructionState CurrentState = EMVCDDestructionState::Healthy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	FMVCDDestructionSettings Settings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MVCD|Destruction")
	UGeometryCollectionComponent* GeometryCollectionComponent = nullptr;

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void CacheGeometryCollectionComponent();

	UFUNCTION()
	void OnRep_CurrentIntegrity();

	UFUNCTION()
	void OnRep_CurrentState();
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};