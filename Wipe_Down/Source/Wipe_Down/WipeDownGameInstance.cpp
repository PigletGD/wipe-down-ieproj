// Fill out your copyright notice in the Description page of Project Settings.


#include "WipeDownGameInstance.h"
#include "Tower.h"

void UWipeDownGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Initialized Game Instance"));

	this->ResetValues();
}

void UWipeDownGameInstance::ResetValues()
{
	this->money = 10;

	this->levelHolySeat = 1;
	this->levelShooting = 1;
	this->levelWall = 1;
	this->levelBathBomb = 1;

	this->wallHealthPUActive = false;
	this->shootingRatePUActive = false;
	this->holySeatRatePUActive = false;
}

void UWipeDownGameInstance::AddMoney(int value)
{
	this->money += value;
}

int UWipeDownGameInstance::GetMoney()
{
	return this->money;
}

void UWipeDownGameInstance::SpendMoney(int value)
{
	this->money -= value;
}

void UWipeDownGameInstance::HealMainTower(int value)
{
	ATower* temp = Cast<ATower>(this->holySeat);
	temp->currentTowerHealth += value;

	if (temp->currentTowerHealth > temp->maxTowerHealth)
		temp->currentTowerHealth = temp->maxTowerHealth;
}