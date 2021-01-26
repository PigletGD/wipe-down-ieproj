// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicShootingTower.h"
#include "ScatPlayer.h"
#include "DrawDebugHelpers.h"
#include "WipeDownGameMode.h"
#include "TowerProjectile.h"

ABasicShootingTower::ABasicShootingTower()
{
	//UE_LOG(LogTemp, Warning, TEXT("Basic Shooting Tower Constructor"));

	this->sphereRadius = 300.0f;

	this->CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->CollisionSphere->InitSphereRadius(this->sphereRadius);
	this->CollisionSphere->SetCollisionProfileName("Trigger");
	this->CollisionSphere->SetupAttachment(this->RootComponent);

	this->CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,
		&ABasicShootingTower::OnOverlapBegin);

	this->CollisionSphere->OnComponentEndOverlap.AddDynamic(this,
		&ABasicShootingTower::OnOverlapEnd);

	this->towerActionRate = 5;
}

void ABasicShootingTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*DrawDebugSphere(this->GetWorld(), this->GetActorLocation(), sphereRadius, 20,
		FColor::Purple, false, -1, 0, 1);*/
}

void ABasicShootingTower::RunAction()
{
	//UE_LOG(LogTemp, Warning, TEXT("Basic Shooting Tower Action Run"));
	AWipeDownGameMode* GM = (AWipeDownGameMode*)this->GetWorld()->GetAuthGameMode();
	ATowerProjectile* bullet = (ATowerProjectile*)GM->bulletPool->RequestPoolable();

	//if (bullet == nullptr) UE_LOG(LogTemp, Warning, TEXT("Bullet is null"));
	//if (targets.Num() <= 0) UE_LOG(LogTemp, Warning, TEXT("Target is null"));

	if (targets.Num() > 0) bullet->BulletSetup(targets[0], 1, this->GetActorLocation());
}

bool ABasicShootingTower::ActionCondition()
{
	if (targets.Num() > 0) return true;

	return false;
}

void ABasicShootingTower::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if ((OtherActor->IsA(AScatEnemy::StaticClass())) && (OtherActor != this) && (OtherComp->GetClass() != USphereComponent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Basic Shooting Something entered: %s + %s"), *OtherActor->GetName(), *OtherComp->GetName());
		targets.Add((AScatEnemy*)OtherActor);
	}
}

void ABasicShootingTower::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor->IsA(AScatEnemy::StaticClass())) && (OtherActor != this) && (OtherComp->GetClass() != USphereComponent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Basic Shooting Something exited: %s + %s"), *OtherActor->GetName(), *OtherComp->GetName());
		targets.Remove((AScatEnemy*)OtherActor);
	}
}