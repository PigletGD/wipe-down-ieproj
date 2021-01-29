// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API AScatPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnRotateCamera(float Axis);
	void OnBuild();
	void OnCancelBuild();
	void OnToggleBuild();
};
