// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "WipeDownGameInstance.h"
#include "Sound/SoundWave.h"
#include "Tower.generated.h"

UCLASS()
class WIPE_DOWN_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TakeDamage(float damage);
	void Die();

	virtual bool ActionCondition();
	virtual void RunAction();

	void SetCoords(int x, int y);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int maxTowerHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float towerActionRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float towerPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int currentTowerHealth;

	float currentActionTick;

	int xCoord;
	int yCoord;

	UWipeDownGameInstance* gameInstance;
private:
	//UPROPERTY(EditAnywhere) UPrimitiveComponent* base;
	//UPROPERTY(EditAnywhere) USphereComponent* sphereCollider;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere) USoundWave* FireSound;
	UPROPERTY(EditAnywhere) USoundWave* DestroySound;
};