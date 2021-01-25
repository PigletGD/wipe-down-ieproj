// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "ScatEnemy.h"
#include "BasicShootingTower.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API ABasicShootingTower : public ATower
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABasicShootingTower();
	virtual void Tick(float DeltaTime) override;

	virtual bool ActionCondition() override;
	virtual void RunAction() override;

	TArray<AScatEnemy*> targets;

	UPROPERTY(VisibleAnywhere) USphereComponent* CollisionSphere;

	float sphereRadius;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
