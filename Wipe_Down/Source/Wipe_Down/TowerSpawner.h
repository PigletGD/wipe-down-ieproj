// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIPE_DOWN_API UTowerSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTowerSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> Tower;
	AActor* Spawned = nullptr;
	FHitResult HitResult;

	UPROPERTY(EditAnywhere) float Distance = 1000.0f;

	void PutAtPointer();
	void Spawn();
	void Despawn();
	void SetInput();
	void Create();
};
