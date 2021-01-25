// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LoadingScreenModule.generated.h"

// Module interface for the game's loading screens
UINTERFACE(MinimalAPI)
class ILoadingScreenModule : public IModuleInterface
{
public:
	// loads the module so it can be turned on
	static inline ILoadingScreenModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ILoadingScreenModule>("LoadingScreenModule");
	}

	//Kicks off the loading screen for in game loading (not startup)
	virtual void StartInGameLoadingScreen(bool playUntilStopped, float playTime) = 0;

	//Stops the Loading Screen
	virtual void StopInGameLoadingScreen() = 0;
	
};

