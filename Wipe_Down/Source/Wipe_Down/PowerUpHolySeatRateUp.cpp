// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpHolySeatRateUp.h"

void APowerUpHolySeatRateUp::Buff()
{
	UE_LOG(LogTemp, Warning, TEXT("Holy Seat Rate Power Up Buff"));

	this->currentTicks = 0;
	this->buffActive = true;

	this->gameInstance->holySeatRatePUActive = true;

	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void APowerUpHolySeatRateUp::EndBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Holy Seat Rate Power Up End Buff"));

	this->buffActive = false;

	this->gameInstance->holySeatRatePUActive = false;

	// release
	this->gameMode->holySeatRatePUPool->ReleasePoolable((APoolableActor*)this);
}