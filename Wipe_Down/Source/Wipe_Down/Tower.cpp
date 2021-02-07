// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "WipeDownGameMode.h"

// Sets default values
ATower::ATower()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructed Tower"));

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
	
	UE_LOG(LogTemp, Warning, TEXT("Begin Play Tower"));

	this->currentActionTick = 0;
	this->currentTowerHealth = this->maxTowerHealth;

	this->gameInstance = (UWipeDownGameInstance*)this->GetWorld()->GetGameInstance();
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
	AWipeDownGameMode* wipeDownGameMode = (AWipeDownGameMode*)GetWorld()->GetAuthGameMode();
	AGrid* grid = wipeDownGameMode->GetGrid();
	UGameplayStatics::PlaySound2D(this, DestroySound);
	if (grid->TileOccupied(this->xCoord, this->yCoord)) {
		grid->RemoveTileOccupation(this->xCoord, this->yCoord);
	}

	this->Destroy();
}

bool ATower::ActionCondition()
{
	return true;
}

void ATower::RunAction()
{
	UGameplayStatics::PlaySound2D(this, FireSound);
	//UE_LOG(LogTemp, Warning, TEXT("Running an action from base class"));
}

void ATower::SetCoords(int x, int y)
{
	this->xCoord = x;
	this->yCoord = y;
}