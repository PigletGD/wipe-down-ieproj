// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSpawner.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATowerSpawner::ATowerSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATowerSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

