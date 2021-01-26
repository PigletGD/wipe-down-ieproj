// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	UFUNCTION(BlueprintCallable, Category = "Money") void AddMoney(int value);
	UFUNCTION(BlueprintCallable, Category = "Money") int GetMoney();
	UFUNCTION(BlueprintCallable, Category = "Money") void SpendMoney(int value);

	UPROPERTY(BlueprintReadWrite) int money = 0;
};
