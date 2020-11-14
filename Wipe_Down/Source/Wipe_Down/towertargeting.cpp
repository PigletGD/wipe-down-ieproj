// Fill out your copyright notice in the Description page of Project Settings.


#include "towertargeting.h"

// Sets default values for this component's properties
Utowertargeting::Utowertargeting()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Utowertargeting::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->shperecollider->SetSphereRadius(200);
}


// Called every frame
void Utowertargeting::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

