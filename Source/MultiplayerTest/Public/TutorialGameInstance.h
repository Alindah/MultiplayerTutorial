// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TutorialGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEST_API UTutorialGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Step 1: Declare constructor and create it in the .cpp file
	UTutorialGameInstance();

protected:
	// Step 2: Function to handle everything that needs to happen when the game instance is created
	virtual void Init() override;
};

