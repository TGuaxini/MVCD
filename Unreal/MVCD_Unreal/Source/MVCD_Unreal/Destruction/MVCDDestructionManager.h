// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVCDDestructionEvent.h"
#include "MVCDDestructionComponent.h"
#include "GameFramework/Actor.h"
#include "MVCDDestructionManager.generated.h"

UCLASS()
class MVCD_UNREAL_API AMVCDDestructionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMVCDDestructionManager();

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void RegisterDestructibleActor(AActor* DestructibleActor);

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void UnregisterDestructibleActor(AActor* DestructibleActor);

	UFUNCTION(BlueprintCallable, Category = "MVCD|Destruction")
	void ProcessDestructionEvent(const FMVCDDestructionEvent& DestructionEvent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MVCD|Destruction")
	TArray<AActor*> RegisteredDestructibleActors;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
