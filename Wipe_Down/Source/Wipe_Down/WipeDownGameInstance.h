// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "WipeDownGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WIPE_DOWN_API UWipeDownGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable) void ResetValues();

	UFUNCTION(BlueprintCallable, Category = "Money") void AddMoney(int value);
	UFUNCTION(BlueprintCallable, Category = "Money") int GetMoney();
	UFUNCTION(BlueprintCallable, Category = "Money") void SpendMoney(int value);
	UFUNCTION(BlueprintCallable, Category = "Heal") void HealMainTower(int value);

	UPROPERTY(BlueprintReadWrite) int money = 0;

	UPROPERTY(BlueprintReadWrite) int levelHolySeat = 1;
	UPROPERTY(BlueprintReadWrite) int levelShooting = 1;
	UPROPERTY(BlueprintReadWrite) int levelWall = 1;
	UPROPERTY(BlueprintReadWrite) int levelBathBomb = 1;

	UPROPERTY(BlueprintReadWrite) bool wallHealthPUActive = false;
	UPROPERTY(BlueprintReadWrite) bool shootingRatePUActive = false;
	UPROPERTY(BlueprintReadWrite) bool holySeatRatePUActive = false;
	UPROPERTY(BlueprintReadWrite) bool isPaused = false;

	UPROPERTY(BlueprintReadWrite) AActor* holySeat;
};