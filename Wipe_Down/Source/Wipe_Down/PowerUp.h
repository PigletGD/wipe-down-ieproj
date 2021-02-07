// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PoolableActor.h"
#include "WipeDownGameMode.h"
#include "WipeDownGameInstance.h"
#include "PowerUp.generated.h"

UCLASS()
class WIPE_DOWN_API APowerUp : public APoolableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere) USphereComponent* CollisionSphere;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	float sphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float buffTime;
	virtual void Buff();
	virtual void EndBuff();

protected:
	AWipeDownGameMode* gameMode;
	UWipeDownGameInstance* gameInstance;

	bool buffActive = false;
	float currentTicks = 0;
};
