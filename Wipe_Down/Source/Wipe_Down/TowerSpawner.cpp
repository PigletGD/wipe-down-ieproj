// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSpawner.h"


// Sets default values for this component's properties
UTowerSpawner::UTowerSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTowerSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...

	UInputComponent* InputComponent = this->GetOwner()->FindComponentByClass<UInputComponent>();

	if(InputComponent != nullptr)
	{
		// spawn by pressing t or left mouse button
		
		InputComponent->BindAction("SpawnTower", EInputEvent::IE_Pressed, this, &UTowerSpawner::Spawn);
		InputComponent->BindAction("Spawn", EInputEvent::IE_Pressed, this, &UTowerSpawner::Spawn);
	}
	
}


// Called every frame
void UTowerSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	PutAtPointer();

}

void UTowerSpawner::PutAtPointer()
{
	if(Spawned != nullptr)
	{
		FVector location;
		FRotator rotation;
		this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
		FVector lineTraceEnd = location + rotation.Vector() * this->Distance;

		FHitResult hitResult;
		FCollisionQueryParams traceParams(FName(TEXT("tracequery")), false, this->GetOwner());
		FCollisionObjectQueryParams objectTypeParams(ECollisionChannel::ECC_WorldStatic);
		this->GetWorld()->LineTraceSingleByObjectType(hitResult, location, lineTraceEnd, objectTypeParams, traceParams);

		if(hitResult.GetActor() == nullptr)
		{
			this->Spawned->SetActorLocation(lineTraceEnd);
			this->Spawned->SetActorHiddenInGame(true);
		}
		else
		{
			this->Spawned->SetActorHiddenInGame(false);
			FVector origin;
			FVector bounds;
			this->Spawned->GetActorBounds(false, origin, bounds, false);
			FVector newPosition = hitResult.ImpactPoint + FVector(0, 0, bounds.Z);
			this->Spawned->SetActorLocation(newPosition);
		}
	}
}

void UTowerSpawner::Spawn()
{
	if (Spawned == nullptr)
	{
		FVector location = this->GetOwner()->GetActorLocation();
		FRotator rotation = this->GetOwner()->GetActorRotation();

		if (Tower != nullptr)
			this->Spawned = GetWorld()->SpawnActor<AActor>(Tower, location, rotation);
	}
	else
	{
		Spawned = nullptr;
	}
}

