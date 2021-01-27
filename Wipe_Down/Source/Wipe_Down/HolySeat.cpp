// Fill out your copyright notice in the Description page of Project Settings.


#include "HolySeat.h"

void AHolySeat::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play Holy Seat"));

	gameInstance = Cast<UWipeDownGameInstance>(GetWorld()->GetGameInstance());
}

void AHolySeat::RunAction()
{
	gameInstance->AddMoney(moneyGeneration);
}