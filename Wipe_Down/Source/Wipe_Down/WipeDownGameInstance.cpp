// Fill out your copyright notice in the Description page of Project Settings.


#include "WipeDownGameInstance.h"

void UWipeDownGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Initialized Game Instance"));

	this->ResetValues();
}

void UWipeDownGameInstance::ResetValues()
{
	this->money = 0;
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