// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PoolableCharacter.h"
#include "Tower.h"
#include "ScatEnemy.generated.h"

UCLASS()
class WIPE_DOWN_API AScatEnemy : public APoolableCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AScatEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int currentHealth;
	float currentAttackTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float enemyAttackRate;

	void TakeDamage(int damage);
	void Attack();
	bool AttackCondition();

	TArray<ATower*> targets;

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