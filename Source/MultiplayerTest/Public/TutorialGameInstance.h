// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
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
	// Part of Step 4: Declare a pointer variable to hold our session interface
	// Make sure to include Interfaces/OnlineSessionInterface.h at the top of this file
	IOnlineSessionPtr SessionInterface;

	// Step 2: Function to handle everything that needs to happen when the game instance is created
	// Note: virtual just makes it easy to override in the future
	virtual void Init() override;

	// Step 6: Determine what we do when a session is created
	// Refer to documentation for IOnlineSession: 
	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Plugins/OnlineSubsystem/IOnlineSession?application_version=5.7
	// Refer to virtual void TriggerOnCreateSessionCompleteDelegates ( FName Param1, bool Param2 )
	virtual void OnCreateSessionComplete(FName ServerName, bool IsSuccessful);

	// Step 5: Create our blueprint function for creating/joining a session
	UFUNCTION(BlueprintCallable) // This just makes our function visible to Blueprints. Neato!
		void CreateServer();

	UFUNCTION(BlueprintCallable)
		void JoinServer();
};

