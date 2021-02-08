// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpInstantMoneyUp.h"

void APowerUpInstantMoneyUp::Buff()
{
	this->gameInstance->AddMoney(this->moneyGain);

	// release
	this->gameMode->instantMoneyPUPool->ReleasePoolable((APoolableActor*)this);
}