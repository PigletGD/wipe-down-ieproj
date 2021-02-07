// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSpawner.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


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

	SetInput();


	APlayerController* PlayerController = this->GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = true;
	
	
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

		FVector mousePos;
		FVector mouseRot;
		
		
		this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
		

		APlayerController* PlayerController = this->GetWorld()->GetFirstPlayerController();

		//get mouseposition onto world. out mousePos, out mouseRot
		PlayerController->DeprojectMousePositionToWorld(mousePos, mouseRot);

		FVector lineTraceEnd = location + mouseRot * this->Distance;

		//get hitresult
		FCollisionQueryParams traceParams(FName(TEXT("tracequery")), false, this->GetOwner());
		FCollisionObjectQueryParams objectTypeParams(ECollisionChannel::ECC_WorldStatic);
		this->GetWorld()->LineTraceSingleByObjectType(HitResult, location, lineTraceEnd, objectTypeParams, traceParams);
		
		if(HitResult.GetActor() == nullptr)
		{
			this->Spawned->SetActorHiddenInGame(true);
		}
		else
		{
			this->Spawned->SetActorHiddenInGame(false);
			FVector origin;
			FVector bounds;
			this->Spawned->GetActorBounds(false, origin, bounds, false);
			UStaticMeshComponent* staticmesh = this->Spawned->FindComponentByClass<UStaticMeshComponent>();

			FVector newPosition;
			if (staticmesh == nullptr)
			{
				newPosition = HitResult.ImpactPoint + FVector(0, 0, bounds.Z);
				UE_LOG(LogTemp, Warning, TEXT("Static Mesh is Null"));
			}
			else
			{
				FVector min;
				FVector max;
				staticmesh->GetLocalBounds(min, max);
				newPosition = HitResult.ImpactPoint + FVector(0, 0, max.Z);
			}
			


			this->Spawned->SetActorLocation(newPosition);

			FRotator rotator = *new FRotator(0,0,0);
			this->Spawned->SetActorRotation(rotator);
		}
	}
}

void UTowerSpawner::Spawn()
{
	if (Spawned == nullptr)
	{
		FVector location = this->GetOwner()->GetActorLocation();
		FRotator rotation = this->GetOwner()->GetActorRotation();

		if (Tower != nullptr) {
			this->Spawned = GetWorld()->SpawnActor<AActor>(Tower, location, rotation);
			UGameplayStatics::PlaySound2D(this, CreateSound);
		}
	}
	else if (HitResult.GetActor() != nullptr)
	{
		Spawned = nullptr;
	}

	UE_LOG(LogTemp, Warning, TEXT("Spawned"));
}

void UTowerSpawner::Despawn()
{
	if (Spawned != nullptr)
	{
		Spawned->Destroy();

		Spawned = nullptr;
	}
}

void UTowerSpawner::SetInput()
{
	UInputComponent* InputComponent = this->GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent != nullptr)
	{
		// spawn by pressing t or left mouse button

		InputComponent->BindAction("SpawnTower", EInputEvent::IE_Pressed, this, &UTowerSpawner::Spawn);
		InputComponent->BindAction("Spawn", EInputEvent::IE_Pressed, this, &UTowerSpawner::Spawn);
		InputComponent->BindAction("CancelSpawn", IE_Pressed, this, &UTowerSpawner::Despawn);
	}
}

void UTowerSpawner::Create()
{
}

