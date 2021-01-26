// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower_BP.h"

// Sets default values for this component's properties
UTower_BP::UTower_BP()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTower_BP::BeginPlay()
{
	Super::BeginPlay();
	//if(this->GetOwner()->FindComponentByClass<USphereComponent>() != NULL)
	UE_LOG(LogTemp, Warning, TEXT("%f"), this->GetOwner()->FindComponentByClass<USphereComponent>());
	// ...
	
}


// Called every frame
void UTower_BP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

