// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolActor.h"

// Sets default values for this component's properties
UObjectPoolActor::UObjectPoolActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPoolActor::BeginPlay()
{
	Super::BeginPlay();

	// ...

	this->Initialize();
}

void UObjectPoolActor::BeginDestroy()
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
void UObjectPoolActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectPoolActor::Initialize()
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
		APoolableActor* poolableObject = this->GetWorld()->SpawnActor<APoolableActor>(this->actorCopy->GetClass(), spawnParams);
		poolableObject->SetIndex(i);
		poolableObject->OnInitialize();
		this->availableObjects.Push(poolableObject);
	}
}

bool UObjectPoolActor::HasObjectAvailable(int requestSize)
{
	return this->availableObjects.Num() > 0;
}

int UObjectPoolActor::GetMaxPoolSize()
{
	return this->maxPoolSize;
}

APoolableActor* UObjectPoolActor::RequestPoolable()
{
	if (this->HasObjectAvailable(1))
	{
		//UE_LOG(LogTemp, Display, TEXT("Now"));

		APoolableActor* object = this->availableObjects.Pop();
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

TArray<APoolableActor*> UObjectPoolActor::RequestPoolableBatch(int size)
{
	TArray<APoolableActor*> objects;
	for (int i = 0; i < size && this->availableObjects.Num(); i++)
	{
		objects.Push(this->RequestPoolable());
	}

	return objects;
}

void UObjectPoolActor::ReleasePoolable(APoolableActor* poolableObject)
{
	poolableObject->OnRelease();
	this->usedObjects.Remove(poolableObject);
	this->availableObjects.Push(poolableObject);
}

void UObjectPoolActor::ReleasePoolableBatch(TArray<APoolableActor*> objectList)
{
	for (int i = 0; i < objectList.Num(); i++)
	{
		this->ReleasePoolable(objectList[i]);
	}
}