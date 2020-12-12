// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraMovement.h"

// Sets default values for this component's properties
UCameraMovement::UCameraMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...

	
	SetInput();
}


// Called every frame
void UCameraMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	Movement(DeltaTime);
}

void UCameraMovement::SetInput()
{
	UInputComponent* InputComponent = this->GetOwner()->FindComponentByClass<UInputComponent>();

	if(InputComponent != nullptr)
	{
		InputComponent->BindAxis("MoveX", this, &UCameraMovement::MoveX);
		InputComponent->BindAxis("MoveY", this, &UCameraMovement::MoveY);
		UE_LOG(LogTemp, Warning, TEXT("Inputcomponent is active"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inputcomponent is null"));
	}
}

void UCameraMovement::MoveX(float value)
{
	this->MovementX = FMath::Clamp(value, -1.0f, 1.0f);
}

void UCameraMovement::MoveY(float value)
{
	this->MovementY = FMath::Clamp(value, -1.0f, 1.0f);
}

void UCameraMovement::Movement(float DeltaTime)
{
	FVector location = this->GetOwner()->GetTransform().GetLocation();
	location.X += this->MovementX * DeltaTime * this->Speed;
	location.Y += this->MovementY * DeltaTime * this->Speed;

	//UE_LOG(LogTemp, Warning, TEXT("MoveX = %f, MoveY = %f, Speed = %f"), MovementX, MovementY, Speed);
	
	this->GetOwner()->SetActorLocation(location);
}

