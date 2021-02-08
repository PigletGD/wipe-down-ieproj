// Fill out your copyright notice in the Description page of Project Settings.


#include "ScatEnemy.h"
#include "DrawDebugHelpers.h"
#include "WipeDownGameMode.h"

// Sets default values
AScatEnemy::AScatEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructed Enemy Scat"));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UE_LOG(LogTemp, Warning, TEXT("Enemy Constructed"));

	this->sphereRadius = 100.0f;

	this->CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->CollisionSphere->InitSphereRadius(this->sphereRadius);
	this->CollisionSphere->SetCollisionProfileName("Trigger");
	this->CollisionSphere->SetupAttachment(this->RootComponent);

	this->CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,
		&AScatEnemy::OnOverlapBegin);

	this->CollisionSphere->OnComponentEndOverlap.AddDynamic(this,
		&AScatEnemy::OnOverlapEnd);

	this->maxHealth = this->currentHealth = 3;
}

// Called when the game starts or when spawned
void AScatEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Begin Play Enemy Scat"));
}

// Called every frame
void AScatEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*DrawDebugSphere(this->GetWorld(), this->GetActorLocation(), sphereRadius, 20,
		FColor::Purple, false, -1, 0, 1);*/

	this->currentAttackTick += DeltaTime;

	if (this->currentAttackTick >= this->enemyAttackRate && this->AttackCondition()) {
		this->currentAttackTick = 0;
		this->Attack();
	}
}

// Called to bind functionality to input
void AScatEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AScatEnemy::TakeDamage(int damage) {
	this->currentHealth -= damage;

	if (this->currentHealth <= 0) {
		this->currentHealth = 0;

		AWipeDownGameMode* GM = (AWipeDownGameMode*)this->GetWorld()->GetAuthGameMode();
		GM->ReduceNumberOfEnemies();

		int randNum = FMath::RandRange(0, 100);

		if (randNum >= 70) {
			int randPool = FMath::RandRange(0, 4);
			
			AActor* actorPU;

			switch (randPool) {
			case 0:
				actorPU = GM->holySeatRatePUPool->RequestPoolable();

				if (actorPU != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("Missing Holy Seat Upgrade"));
					actorPU->SetActorLocation(this->GetActorLocation());
				}
				break;
			case 1:
				actorPU = GM->wallHealthPUPool->RequestPoolable();
				
				if (actorPU != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("Missing Wall Health Upgrade"));
					actorPU->SetActorLocation(this->GetActorLocation());
				}
				break;
			case 2:
				actorPU = GM->shootingRatePUPool->RequestPoolable();
				
				if (actorPU != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("Missing Shooting Upgrade"));
					actorPU->SetActorLocation(this->GetActorLocation());
				}
				break;
			case 3:
				actorPU = GM->instantHealthPUPool->RequestPoolable();

				if (actorPU != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("Missing Health Upgrade"));
					actorPU->SetActorLocation(this->GetActorLocation());
				}
				break;
			case 4:
				actorPU = GM->instantMoneyPUPool->RequestPoolable();

				if (actorPU != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("Missing Money Upgrade"));
					actorPU->SetActorLocation(this->GetActorLocation());
				}
				break;
			}
		}

		// Return to object pool
		GM->basicEnemyPool->ReleasePoolable((APoolableCharacter*)this);
	}
}

void AScatEnemy::Attack()
{
	//UE_LOG(LogTemp, Warning, TEXT("Enemy Scat Attacked"));

	targets[0]->TakeDamage(1);
}

bool AScatEnemy::AttackCondition()
{
	if (targets.Num() > 0) return true;

	return false;
}

void AScatEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if ((OtherActor->GetClass()->IsChildOf(ATower::StaticClass())) && (OtherActor != this) && (OtherComp->GetClass() != USphereComponent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Enemy Scat Something entered: %s + %s"), *OtherActor->GetClass()->GetName(), *OtherComp->GetName());
		targets.Add((ATower*)OtherActor);
	}
}

void AScatEnemy::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor->GetClass()->IsChildOf(ATower::StaticClass())) && (OtherActor != this) && (OtherComp->GetClass() != USphereComponent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Enemy Scat Something exited: %s + %s"), *OtherActor->GetName(), *OtherComp->GetName());
		targets.Remove((ATower*)OtherActor);
	}
}