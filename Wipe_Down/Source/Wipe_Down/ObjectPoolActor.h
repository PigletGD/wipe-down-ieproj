// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolableActor.h"
#include "ObjectPoolActor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIPE_DOWN_API UObjectPoolActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Initialize();
	bool HasObjectAvailable(int requestSize);
	int GetMaxPoolSize();
	APoolableActor* RequestPoolable();
	TArray<APoolableActor*> RequestPoolableBatch(int size);

	void ReleasePoolable(APoolableActor* poolableObject);
	void ReleasePoolableBatch(TArray<APoolableActor*> objectList);
	void ReleasePoolableBatch(int count);

private:
	UPROPERTY(EditAnywhere) int maxPoolSize = 20;
	UPROPERTY(EditAnywhere) APoolableActor* actorCopy = NULL;
	UPROPERTY(EditAnywhere) AActor* parent = NULL;

	TArray<APoolableActor*> availableObjects;
	TArray<APoolableActor*> usedObjects;
};