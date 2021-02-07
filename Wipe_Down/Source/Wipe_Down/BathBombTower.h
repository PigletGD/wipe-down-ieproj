// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "ScatEnemy.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "BathBombTower.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API ABathBombTower : public ATower
{
	GENERATED_BODY()

public:
	ABathBombTower();
	virtual void Tick(float DeltaTime) override;

	virtual bool ActionCondition() override;
	virtual void RunAction() override;
	void BlowUp();

	TArray<AScatEnemy*> targets;

	UPROPERTY(VisibleAnywhere) USphereComponent* CollisionSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) URadialForceComponent* RadialForce;

	float sphereRadius;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnywhere) USoundWave* ExplosionSound;
private:
	float currentTicks = 0;
	bool triggerActivated = false;
};
