// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolActor.h"
#include "ObjectPoolCharacter.h"
#include "PoolableActorController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIPE_DOWN_API UPoolableActorController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPoolableActorController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UObjectPoolActor* objectPoolComponent;
	UObjectPoolCharacter* objectPoolComponent;

	float ticks = 0.0f;
	UPROPERTY(EditAnywhere) float INTERVAL = 0.5f;
};
