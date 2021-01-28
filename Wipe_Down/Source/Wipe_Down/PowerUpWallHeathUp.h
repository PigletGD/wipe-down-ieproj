// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "PowerUpWallHeathUp.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API APowerUpWallHeathUp : public APowerUp
{
	GENERATED_BODY()
	
public:
	virtual void Buff() override;
	virtual void EndBuff() override;
};