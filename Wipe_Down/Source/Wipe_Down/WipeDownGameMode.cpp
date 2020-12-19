





// Fill out your copyright notice in the Description page of Project Settings.


#include "WipeDownGameMode.h"

AWipeDownGameMode::AWipeDownGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AWipeDownGameMode::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGrid::StaticClass(), FoundActors);

    if (FoundActors.Num() > 0) {
        this->grid = (AGrid*)FoundActors[0];
        UE_LOG(LogTemp, Warning, TEXT("Grid found"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Grid not found"));
}

AGrid* AWipeDownGameMode::GetGrid() const {
    return this->grid;
}