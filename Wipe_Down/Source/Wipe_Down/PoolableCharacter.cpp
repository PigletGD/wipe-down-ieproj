// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolableCharacter.h"

// Sets default values
APoolableCharacter::APoolableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolableCharacter::BeginPlay() 
{
	Super::BeginPlay();

	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->SetActorTickEnabled(false);
}

// Called every frame
void APoolableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolableCharacter::OnInitialize()
{
	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->SetActorTickEnabled(false);
}

void APoolableCharacter::OnActivate()
{
	this->SetActorHiddenInGame(false);
	this->SetActorEnableCollision(true);
	this->SetActorTickEnabled(true);
}

void APoolableCharacter::OnRelease()
{
	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->SetActorTickEnabled(false);
}

void APoolableCharacter::SetIndex(int i)
{
	this->index = 1;
}

int APoolableCharacter::GetIndex()
{
	return this->index;
}

// Called to bind functionality to input
void APoolableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

