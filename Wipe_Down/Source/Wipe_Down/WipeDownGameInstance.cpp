// Fill out your copyright notice in the Description page of Project Settings.


#include "WipeDownGameInstance.h"

void UWipeDownGameInstance::Init()
{
	Super::Init();

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