// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpWallHeathUp.h"

void APowerUpWallHeathUp::Buff()
{
	UE_LOG(LogTemp, Warning, TEXT("Wall Health Power Up Buff"));

	this->currentTicks = 0;
	this->buffActive = true;

	this->gameInstance->wallHealthPUActive = true;

	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void APowerUpWallHeathUp::EndBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Wall Health Power Up End Buff"));

	this->buffActive = false;

	this->gameInstance->wallHealthPUActive = false;

	// release
	this->gameMode->wallHealthPUPool->ReleasePoolable((APoolableActor*)this);
}