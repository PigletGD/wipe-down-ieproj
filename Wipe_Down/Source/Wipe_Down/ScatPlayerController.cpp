// Fill out your copyright notice in the Description page of Project Settings.


#include "ScatPlayerController.h"
#include "ScatPlayer.h"

void AScatPlayerController::BeginPlay()
{

	UInputComponent* inputComponent = this->FindComponentByClass<UInputComponent>();

	inputComponent->BindAxis("MoveForward", this, &AScatPlayerController::OnMoveForward);
	inputComponent->BindAxis("MoveRight", this, &AScatPlayerController::OnMoveRight);
	inputComponent->BindAxis("CamRotate", this, &AScatPlayerController::OnRotateCamera);
	inputComponent->BindAction("Spawn", IE_Pressed, this, &AScatPlayerController::OnBuild);
	inputComponent->BindAction("ToggleBuild", IE_Pressed, this, &AScatPlayerController::OnToggleBuild).bConsumeInput = false;
	inputComponent->BindAction("CancelBuild", IE_Pressed, this, &AScatPlayerController::OnCancelBuild);
}

void AScatPlayerController::OnMoveForward(float Axis)
{
	AScatPlayer* scatPlayer = (AScatPlayer*)this->GetPawn<AScatPlayer>();

	if (scatPlayer != nullptr)
		scatPlayer->MoveForward(Axis);
}

void AScatPlayerController::OnMoveRight(float Axis)
{
	AScatPlayer* scatPlayer = (AScatPlayer*)this->GetPawn<AScatPlayer>();

	if (scatPlayer != nullptr)
		scatPlayer->MoveRight(Axis);
}

void AScatPlayerController::OnRotateCamera(float Axis)
{
	AScatPlayer* scatPlayer = (AScatPlayer*)this->GetPawn<AScatPlayer>();

	if (scatPlayer != nullptr)
		scatPlayer->RotateCamera(Axis);
}

void AScatPlayerController::OnBuild()
{
	AScatPlayer* scatPlayer = (AScatPlayer*)this->GetPawn<AScatPlayer>();

	if (scatPlayer != nullptr)
		scatPlayer->Build();
}

void AScatPlayerController::OnCancelBuild()
{
	AScatPlayer* scatPlayer = (AScatPlayer*)this->GetPawn<AScatPlayer>();

	if (scatPlayer != nullptr)
		scatPlayer->CancelBuild();
}

void AScatPlayerController::OnToggleBuild()
{
	AScatPlayer* scatPlayer = (AScatPlayer*)this->GetPawn<AScatPlayer>();

	if (scatPlayer != nullptr)
		scatPlayer->ToggleBuild();
}