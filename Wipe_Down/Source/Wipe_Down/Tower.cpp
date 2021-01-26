// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	
	this->BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	this->BaseMesh->SetupAttachment(RootComponent);

	//UE_LOG(LogTemp, Warning, TEXT("Tower Constructor"));
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	this->currentActionTick = 0;
	this->currentTowerHealth = this->maxTowerHealth;
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->currentActionTick += DeltaTime;

	if (this->currentActionTick >= this->towerActionRate && this->ActionCondition()) {
		this->currentActionTick = 0;
		this->RunAction();
	}
}

void ATower::TakeDamage(float damage)
{
	this->currentTowerHealth -= damage;
	
	if (this->currentTowerHealth <= 0) {
		this->currentTowerHealth = 0;
		this->Die();
	}
}

void ATower::Die()
{
	//UE_LOG(LogTemp, Warning, TEXT("Tower has been killed"));
	this->Destroy();
}

bool ATower::ActionCondition()
{
	return true;
}

void ATower::RunAction()
{
	//UE_LOG(LogTemp, Warning, TEXT("Running an action from base class"));
}