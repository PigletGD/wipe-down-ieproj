// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerProjectile.h"
#include "WipeDownGameMode.h"

// Sets default values
ATowerProjectile::ATowerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->sphereRadius = 20.0f;

	this->CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->CollisionSphere->InitSphereRadius(this->sphereRadius);
	this->CollisionSphere->SetCollisionProfileName("Trigger");
	this->CollisionSphere->SetupAttachment(this->RootComponent);

	this->CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,
		&ATowerProjectile::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATowerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->target != nullptr && !this->target->IsHidden()) {
		// run move function

		FVector destination = FMath::VInterpConstantTo(this->GetActorLocation(), this->target->GetActorLocation(), DeltaTime, 500.0f);
		this->SetActorLocation(destination);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Target no longer exists"));
		this->target = nullptr;

		// release bullet
		AWipeDownGameMode* GM = (AWipeDownGameMode*)this->GetWorld()->GetAuthGameMode();
		GM->bulletPool->ReleasePoolable((APoolableActor*)this);
	}
}

void ATowerProjectile::BulletSetup(AScatEnemy* newTarget, int newProjectileDamage, FVector newPosition)
{
	this->target = newTarget;
	this->projectileDamage = newProjectileDamage;
	this->SetActorLocation(newPosition);
}

void ATowerProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if ((OtherActor->GetClass()->IsChildOf(AScatEnemy::StaticClass())) && (OtherActor != this) && (OtherComp->GetClass() != USphereComponent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Bullet Landed: %s + %s"), *OtherActor->GetClass()->GetName(), *OtherComp->GetName());

		AScatEnemy* hit = (AScatEnemy*)OtherActor;
		hit->TakeDamage(this->projectileDamage);

		// release bullet
		AWipeDownGameMode* GM = (AWipeDownGameMode*)this->GetWorld()->GetAuthGameMode();
		GM->bulletPool->ReleasePoolable((APoolableActor*)this);
	}
}