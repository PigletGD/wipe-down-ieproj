// Fill out your copyright notice in the Description page of Project Settings.


#include "WallTower.h"

void AWallTower::RunAction()
{
	this->currentTowerHealth += 1;

	if (this->currentTowerHealth > this->maxTowerHealth)
		this->currentTowerHealth = this->maxTowerHealth;
}

bool AWallTower::ActionCondition()
{
	return this->gameInstance->wallHealthPUActive;
}