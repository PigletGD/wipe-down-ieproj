// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolableActorController.h"

// Sets default values for this component's properties
UPoolableActorController::UPoolableActorController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPoolableActorController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	this->objectPoolComponent = this->GetOwner()->FindComponentByClass<UObjectPoolCharacter>();
}


// Called every frame
void UPoolableActorController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	this->ticks += DeltaTime;

	if (this->ticks > this->INTERVAL) {
		this->ticks -= this->INTERVAL;
		this->objectPoolComponent->RequestPoolable();
	}
}