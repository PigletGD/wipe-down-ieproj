// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "WipeDownGameInstance.h"
#include "HolySeat.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API AHolySeat : public ATower
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void RunAction() override;

	UPROPERTY(EditAnywhere) int moneyGeneration = 1;
};