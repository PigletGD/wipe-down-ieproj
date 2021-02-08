// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpInstantHealthUp.h"

void APowerUpInstantHealthUp::Buff()
{
	this->gameInstance->HealMainTower(this->healthGain);

	// release
	this->gameMode->instantHealthPUPool->ReleasePoolable((APoolableActor*)this);
}