// Fill out your copyright notice in the Description page of Project Settings.


#include "HolySeat.h"

void AHolySeat::BeginPlay()
{
	Super::BeginPlay();

	gameInstance = Cast<UWipeDownGameInstance>(GetWorld()->GetGameInstance());
}

void AHolySeat::RunAction()
{
	gameInstance->AddMoney(moneyGeneration);
}