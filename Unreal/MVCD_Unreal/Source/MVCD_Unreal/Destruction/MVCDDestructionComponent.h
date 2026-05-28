// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVCDDestructionEvent.h"
#include "Components/ActorComponent.h"
#include "MVCDDestructionComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MVCD_UNREAL_API UMVCDDestructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMVCDDestructionComponent();

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void ApplyDamage(const FMVCDDestructionEvent& DestructionEvent);

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	bool CanBeDestroyed() const;

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void HandleDestruction(const FMVCDDestructionEvent& DestructionEvent);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	float CurrentIntegrity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVCD|Destruction")
	float DestructionThreshold = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
