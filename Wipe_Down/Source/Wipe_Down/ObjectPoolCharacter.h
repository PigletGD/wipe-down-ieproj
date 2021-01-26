// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolableCharacter.h"
#include "ObjectPoolCharacter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIPE_DOWN_API UObjectPoolCharacter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolCharacter();

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
	UFUNCTION(BlueprintCallable, Category = "Spawn") APoolableCharacter* RequestPoolable();
	UFUNCTION(BlueprintCallable, Category = "Spawn") TArray<APoolableCharacter*> RequestPoolableBatch(int size);

	UFUNCTION(BlueprintCallable, Category = "Spawn") void ReleasePoolable(APoolableCharacter* poolableObject);
	UFUNCTION(BlueprintCallable, Category = "Spawn") void ReleasePoolableBatch(TArray<APoolableCharacter*> objectList);
	//UFUNCTION(BlueprintCallable, Category = "Spawn") void ReleasePoolableBatchCount(int count);

private:
	UPROPERTY(EditAnywhere) int maxPoolSize = 20;
	UPROPERTY(EditAnywhere) APoolableCharacter* actorCopy = NULL;
	UPROPERTY(EditAnywhere) AActor* parent = NULL;

	TArray<APoolableCharacter*> availableObjects;
	TArray<APoolableCharacter*> usedObjects;
};
