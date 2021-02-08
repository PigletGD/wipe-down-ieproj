// Fill out your copyright notice in the Description page of Project Settings.


#include "HolySeat.h"

void AHolySeat::BeginPlay()
{
	Super::BeginPlay();
	CreateSound->Volume = 0;
	UE_LOG(LogTemp, Warning, TEXT("Begin Play Holy Seat"));
}

void AHolySeat::RunAction()
{
	int modifier = 1;
	if (this->gameInstance->holySeatRatePUActive)
		modifier = 2;

	this->gameInstance->AddMoney((moneyGeneration + this->gameInstance->levelHolySeat - 1) * modifier);
}