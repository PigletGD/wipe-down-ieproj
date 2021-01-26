// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolableActor.h"

// Sets default values
APoolableActor::APoolableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolableActor::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->SetActorTickEnabled(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

// Called every frame
void APoolableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolableActor::OnInitialize()
{
	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->SetActorTickEnabled(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void APoolableActor::OnActivate()
{
	this->SetActorHiddenInGame(false);
	this->SetActorEnableCollision(true);
	this->SetActorTickEnabled(true);
	if (this->physicsAffected) this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
}

void APoolableActor::OnRelease()
{
	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->SetActorTickEnabled(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void APoolableActor::SetIndex(int i)
{
	this->index = 1;
}

int APoolableActor::GetIndex()
{
	return this->index;
}