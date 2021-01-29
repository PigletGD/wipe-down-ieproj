// Fill out your copyright notice in the Description page of Project Settings.


#include "BathBombTower.h"
#include "DrawDebugHelpers.h"
#include "WipeDownGameMode.h"

ABathBombTower::ABathBombTower()
{
	//UE_LOG(LogTemp, Warning, TEXT("Basic Shooting Tower Constructor"));

	UE_LOG(LogTemp, Warning, TEXT("Constructed Shooting Tower"));

	this->sphereRadius = 300.0f;

	this->CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->CollisionSphere->InitSphereRadius(this->sphereRadius);
	this->CollisionSphere->SetCollisionProfileName("Trigger");
	this->CollisionSphere->SetupAttachment(this->RootComponent);

	this->RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RFComponent"));
	this->RadialForce->SetupAttachment(this->RootComponent);

	this->CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,
		&ABathBombTower::OnOverlapBegin);

	this->CollisionSphere->OnComponentEndOverlap.AddDynamic(this,
		&ABathBombTower::OnOverlapEnd);

	this->towerActionRate = 5;
}

void ABathBombTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->triggerActivated) {
		this->currentTicks += DeltaTime;

		if (this->currentTicks > 0.2f) {
			this->triggerActivated = false;
			this->BlowUp();
		}
		
	}

	/*DrawDebugSphere(this->GetWorld(), this->GetActorLocation(), sphereRadius, 20,
		FColor::Purple, false, -1, 0, 1);*/
}

void ABathBombTower::RunAction()
{
	this->triggerActivated = true;
}

bool ABathBombTower::ActionCondition()
{
	if (targets.Num() > 0) return true;

	return false;
}

void ABathBombTower::BlowUp()
{
	FVector bombPosition = this->GetActorLocation();
	bombPosition.Z -= 50.0f;

	for (int i = 0; i < targets.Num(); i++) {
		targets[i]->TakeDamage(2);
	}

	this->RadialForce->FireImpulse();

	this->TakeDamage(100000);
}

void ABathBombTower::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if ((OtherActor->IsA(AScatEnemy::StaticClass())) && (OtherActor != this) && (OtherComp->GetClass() != USphereComponent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Basic Shooting Something entered: %s + %s"), *OtherActor->GetName(), *OtherComp->GetName());
		targets.Add((AScatEnemy*)OtherActor);
	}
}

void ABathBombTower::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor->IsA(AScatEnemy::StaticClass())) && (OtherActor != this) && (OtherComp->GetClass() != USphereComponent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Basic Shooting Something exited: %s + %s"), *OtherActor->GetName(), *OtherComp->GetName());
		targets.Remove((AScatEnemy*)OtherActor);
	}
}
