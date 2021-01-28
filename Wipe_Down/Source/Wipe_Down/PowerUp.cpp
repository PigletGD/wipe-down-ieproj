// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "ScatPlayer.h"

// Sets default values
APowerUp::APowerUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructed Power Up"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->sphereRadius = 20.0f;

	this->CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->CollisionSphere->InitSphereRadius(this->sphereRadius);
	this->CollisionSphere->SetCollisionProfileName("Trigger");
	this->CollisionSphere->SetupAttachment(this->RootComponent);

	this->CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,
		&APowerUp::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Begin Play Power Up"));

	this->gameMode = (AWipeDownGameMode*)this->GetWorld()->GetAuthGameMode();
	this->gameInstance = (UWipeDownGameInstance*)this->GetWorld()->GetGameInstance();
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->buffActive) {
		this->currentTicks += DeltaTime;

		if (this->currentTicks > this->buffTime) {
			this->EndBuff();
		}
	}
}

void APowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if ((OtherActor->GetClass()->IsChildOf(AScatPlayer::StaticClass())) && (OtherActor != this) && (OtherComp->GetClass() != USphereComponent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Bullet Landed: %s + %s"), *OtherActor->GetClass()->GetName(), *OtherComp->GetName());

		this->Buff();

		// release bullet
		//AWipeDownGameMode* GM = (AWipeDownGameMode*)this->GetWorld()->GetAuthGameMode();
		//GM->bulletPool->ReleasePoolable((APoolableActor*)this);
	}
}

void APowerUp::Buff()
{
	UE_LOG(LogTemp, Warning, TEXT("Base Power Up Buff"));

	this->currentTicks = 0;
	this->buffActive = true;

	this->SetActorLocation(FVector(-40000, -40000, -40000));
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void APowerUp::EndBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Base Power Up End Buff"));

	this->buffActive = false;

	// release
}