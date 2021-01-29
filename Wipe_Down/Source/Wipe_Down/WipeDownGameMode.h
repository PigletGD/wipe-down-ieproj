// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Grid.h"
#include "ObjectPoolActor.h"
#include "ObjectPoolCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "WipeDownGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API AWipeDownGameMode : public AGameModeBase
{
    GENERATED_BODY() 

public:
    AWipeDownGameMode();
    UFUNCTION(BlueprintCallable, Category = "Game") AGrid* GetGrid() const ;
    UFUNCTION(BlueprintCallable, Category = "Game") int GetMaxEnemies();
    UFUNCTION(BlueprintCallable, Category = "Game") void AddMaxEnemies(int value);
    UFUNCTION(BlueprintCallable, Category = "Game") void NextWave();
    UFUNCTION(BlueprintCallable, Category = "Game") int GetNumberOfEnemies();
    UFUNCTION(BlueprintCallable, Category = "Game") void ReduceNumberOfEnemies();
    UFUNCTION(BlueprintCallable, Category = "Game") void SetNumberOfEnemies(int value);
    UFUNCTION(BlueprintCallable, Category = "Game") void UnloadGrid();

    UPROPERTY(EditAnywhere, BlueprintReadWrite) AGrid* grid;

    int waveNumber = 0;
    int numberOfEnemies;
    int maxEnemies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) UObjectPoolActor* bulletPool;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) UObjectPoolActor* wallHealthPUPool;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) UObjectPoolActor* shootingRatePUPool;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) UObjectPoolActor* holySeatRatePUPool;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) UObjectPoolCharacter* basicEnemyPool;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) UObjectPoolCharacter* tankEnemyPool;

private:
    void BeginPlay() override;
};
