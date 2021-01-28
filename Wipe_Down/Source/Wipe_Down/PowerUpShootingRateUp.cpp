// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpShootingRateUp.h"

void APowerUpShootingRateUp::Buff()
{
	UE_LOG(LogTemp, Warning, TEXT("Shooting Rate Power Up Buff"));

	this->currentTicks = 0;
	this->buffActive = true;

	this->gameInstance->shootingRatePUActive = true;

	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void APowerUpShootingRateUp::EndBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Shooting Rate Power Up End Buff"));

	this->buffActive = false;

	this->gameInstance->shootingRatePUActive = false;

	// release
	this->gameMode->shootingRatePUPool->ReleasePoolable((APoolableActor*)this);
}