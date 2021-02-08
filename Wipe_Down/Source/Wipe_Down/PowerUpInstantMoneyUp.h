// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "PowerUpInstantMoneyUp.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API APowerUpInstantMoneyUp : public APowerUp
{
	GENERATED_BODY()


public:
	virtual void Buff() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int moneyGain = 30;

};