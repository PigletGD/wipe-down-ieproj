// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolCharacter.h"

// Sets default values for this component's properties
UObjectPoolCharacter::UObjectPoolCharacter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPoolCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ...

	this->Initialize();
}

void UObjectPoolCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	for (int i = 0; i < this->availableObjects.Num(); i++)
	{
		this->availableObjects[i]->Destroy();
	}

	for (int i = 0; i < this->usedObjects.Num(); i++)
	{
		this->usedObjects[i]->Destroy();
	}

	this->availableObjects.Empty();
	this->usedObjects.Empty();
}

// Called every frame
void UObjectPoolCharacter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectPoolCharacter::Initialize()
{
	//UE_LOG(LogTemp, Warning, TEXT("Initialized Pool"));

	if (this->actorCopy == NULL)
	{
		//UE_LOG(LogTemp, Display, TEXT("Actor is null. Object pool not initialized"));
		return;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Template = this->actorCopy;
	spawnParams.Owner = this->GetOwner();

	const FTransform transform = this->actorCopy->GetActorTransform();
	for (int i = 0; i < this->maxPoolSize - 1; i++) {
		APoolableCharacter* poolableObject = this->GetWorld()->SpawnActor<APoolableCharacter>(this->actorCopy->GetClass(), spawnParams);
		poolableObject->Controller = nullptr;
		poolableObject->SpawnDefaultController();
		poolableObject->SetIndex(i);
		poolableObject->OnInitialize();
		this->availableObjects.Push(poolableObject);
	}
}

bool UObjectPoolCharacter::HasObjectAvailable(int requestSize)
{
	return this->availableObjects.Num() > 0;
}

int UObjectPoolCharacter::GetMaxPoolSize()
{
	return this->maxPoolSize;
}

APoolableCharacter* UObjectPoolCharacter::RequestPoolable()
{
	if (this->HasObjectAvailable(1))
	{
		//UE_LOG(LogTemp, Display, TEXT("Now"));

		APoolableCharacter* object = this->availableObjects.Pop();
		object->SetIndex(this->usedObjects.Num());
		this->usedObjects.Push(object);
		object->OnActivate();
		object->SetActorTransform(this->GetOwner()->GetActorTransform());
		return object;
	}
	else {
		//UE_LOG(LogTemp, Display, TEXT("No more available objects"));
		return NULL;
	}
}

TArray<APoolableCharacter*> UObjectPoolCharacter::RequestPoolableBatch(int size)
{
	TArray<APoolableCharacter*> objects;
	for (int i = 0; i < size && this->availableObjects.Num(); i++)
	{
		objects.Push(this->RequestPoolable());
	}

	return objects;
}

void UObjectPoolCharacter::ReleasePoolable(APoolableCharacter* poolableObject)
{
	poolableObject->OnRelease();
	this->usedObjects.Remove(poolableObject);
	this->availableObjects.Push(poolableObject);
}

void UObjectPoolCharacter::ReleasePoolableBatch(TArray<APoolableCharacter*> objectList)
{
	for (int i = 0; i < objectList.Num(); i++)
	{
		this->ReleasePoolable(objectList[i]);
	}
}