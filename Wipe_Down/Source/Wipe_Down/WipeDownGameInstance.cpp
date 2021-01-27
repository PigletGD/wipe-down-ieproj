// Fill out your copyright notice in the Description page of Project Settings.


#include "WipeDownGameInstance.h"

void UWipeDownGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Initialized Game Instance"));

	this->money = 0;
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