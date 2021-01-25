// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.h"
#include "ScatEnemy.h"
#include "TowerProjectile.generated.h"

UCLASS()
class WIPE_DOWN_API ATowerProjectile : public APoolableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BulletSetup(AScatEnemy* newTarget, int newProjectileDamage, FVector newPosition);

	UPROPERTY(VisibleAnywhere) USphereComponent* CollisionSphere;

	float sphereRadius;

	AScatEnemy* target;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	int projectileDamage;
};