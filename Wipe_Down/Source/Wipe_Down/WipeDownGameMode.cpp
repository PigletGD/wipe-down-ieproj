// Fill out your copyright notice in the Description page of Project Settings.


#include "WipeDownGameMode.h"

AWipeDownGameMode::AWipeDownGameMode()
{
    UE_LOG(LogTemp, Warning, TEXT("Constructed Game Mode"));
    PrimaryActorTick.bCanEverTick = true;
}

void AWipeDownGameMode::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Begin Play Game Mode"));

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGrid::StaticClass(), FoundActors);

    this->waveNumber = 1;
    this->maxEnemies = 2;
    this->numberOfEnemies = 0;

    if (FoundActors.Num() > 0) {
        this->grid = (AGrid*)FoundActors[0];
        UE_LOG(LogTemp, Warning, TEXT("Grid found"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Grid not found"));
}

AGrid* AWipeDownGameMode::GetGrid() const {
    return this->grid;
}

int AWipeDownGameMode::GetMaxEnemies() {
    return this->maxEnemies;
}

void AWipeDownGameMode::ResetMaxEnemies() {
    this->maxEnemies = 2;
}

void AWipeDownGameMode::AddMaxEnemies(int value) {
    this->maxEnemies += value;
}

int AWipeDownGameMode::GetNumberOfEnemies() {
    //UE_LOG(LogTemp, Warning, TEXT("Max Enemies %d"), this->maxEnemies);
    return this->numberOfEnemies;
}

void AWipeDownGameMode::NextWave() {
    //UE_LOG(LogTemp, Warning, TEXT("Next Wave"));
    this->waveNumber++;
    this->maxEnemies += 2;
}

void AWipeDownGameMode::ReduceNumberOfEnemies() {
    this->numberOfEnemies--;
}

void AWipeDownGameMode::SetNumberOfEnemies(int value) {
    this->numberOfEnemies = value;
}

void AWipeDownGameMode::UnloadGrid() {
    this->grid->UnloadAllOfGrid();
}