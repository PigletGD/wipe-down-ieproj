// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Grid.h"
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
    AGrid* GetGrid() const ;
    UFUNCTION(BlueprintCallable, Category = "Game") int GetMaxEnemies();
    UFUNCTION(BlueprintCallable, Category = "Game") void AddMaxEnemies(int value);
    UFUNCTION(BlueprintCallable, Category = "Game") void NextWave();
    UFUNCTION(BlueprintCallable, Category = "Game") int GetNumberOfEnemies();
    UFUNCTION(BlueprintCallable, Category = "Game") void ReduceNumberOfEnemies();
    UFUNCTION(BlueprintCallable, Category = "Game") void SetNumberOfEnemies(int value);

    AGrid* grid;

    int waveNumber;
    int numberOfEnemies;
    int maxEnemies;

private:
    void BeginPlay() override;
};
