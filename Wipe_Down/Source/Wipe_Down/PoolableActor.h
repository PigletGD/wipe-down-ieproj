// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "PoolableActor.generated.h"

UCLASS()
class WIPE_DOWN_API APoolableActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnInitialize();
	virtual void OnRelease();
	virtual void OnActivate();

	void SetIndex(int i);
	int GetIndex();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool physicsAffected;

private:
	int index = -1;
};
