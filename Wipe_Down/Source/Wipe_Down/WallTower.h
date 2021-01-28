// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "WallTower.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API AWallTower : public ATower
{
	GENERATED_BODY()
	
public:
	virtual bool ActionCondition() override;
	virtual void RunAction() override;
};
