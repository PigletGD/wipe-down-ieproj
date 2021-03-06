// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "WipeDownGameMode.h"
#include "Tower.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "ScatPlayer.generated.h"

UCLASS()
class WIPE_DOWN_API AScatPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AScatPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere) USceneComponent* CameraTargetPoint;
	UPROPERTY(EditAnywhere) USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere) UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere) FVector CameraDistanceOffset = FVector(0.0f, 0.0f, 40.0f);

	AWipeDownGameMode* wipeDownGameMode;

	//UPROPERTY(EditAnywhere) TSubclassOf<AActor> Tower;
	UPROPERTY(EditAnywhere) AActor* Spawned = nullptr;
	FHitResult HitResult;

	UPROPERTY(EditAnywhere) float Distance = 2000.0f;
	UPROPERTY(EditAnywhere) USoundWave* walkingSound;
	UPROPERTY(EditAnywhere) USoundWave* buildSound;
	UPROPERTY(EditAnywhere) USoundWave* bgMusic;

	int row = -90;
	int column = -90;
	bool buildModeOn = false;
	float isMovingForward = false;
	float isMovingSidewards = false;

public:
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void RotateCamera(float Axis);
	void Build();
	void ToggleBuild();
	void CancelBuild();
	void ToggleShooting();
	void ToggleWall();
	void ToggleBathBomb();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) ATower* Tower = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ATower* Shooting = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ATower* Wall = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ATower* BathBomb = nullptr;
private:
	//void InitializeTower();

	float zLocation;

	bool isWalking;
};