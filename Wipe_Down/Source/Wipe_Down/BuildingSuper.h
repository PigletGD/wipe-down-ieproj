// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingSuper.generated.h"

UCLASS()
class WIPE_DOWN_API ABuildingSuper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingSuper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere) float health;
	//production or attack;
	UPROPERTY(EditAnywhere) float Speed;
	UPROPERTY(EditAnywhere) FVector Position;
	UPROPERTY(EditAnywhere) int cost;
	UPROPERTY(EditAnywhere) int Size;
	UPROPERTY(EditAnywhere) UStaticMesh* mesh;

	void initializeVariables(float, float, int, int, FVector);
	FVector GetPosition();
	void setPosition(FVector);
	//idea to all who can see super class to be inherited by everything else

};
