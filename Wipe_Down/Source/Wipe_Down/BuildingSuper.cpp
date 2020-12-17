// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSuper.h"

// Sets default values
ABuildingSuper::ABuildingSuper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ABuildingSuper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingSuper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABuildingSuper::GetPosition()
{
	return this->Position;
}

void ABuildingSuper::setPosition(FVector pos)
{
	this->Position = pos;
}

void ABuildingSuper::initializeVariables(float hp, float spd, int body, int value, FVector pos)
{
	this->health = health;
	this->Speed = spd;
	this->Size = body;
	this->cost = value;
	this->Position = pos;
	//cant find out hown to set static mesh
}


