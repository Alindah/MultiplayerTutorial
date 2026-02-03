// Fill out your copyright notice in the Description page of Project Settings.
// Tutorial: https://www.youtube.com/watch?v=Ed7f6gvd-l4&list=PLnHeglBaPYu9Iyr5jwiCEdKopTq0zvuK7
// Start at Step 1 in TutorialGameInstance.h

#include "TutorialGameInstance.h"

// Step 3: Include the headers for OnlineSubsystem
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

// For Step 6
#include "Engine/World.h"

// Constructor that we added
UTutorialGameInstance::UTutorialGameInstance()
{
	
}

// This is the virtual void Init() override function in the header
// This will decide what happens when the game instance is created
void UTutorialGameInstance::Init()
{
	// Step 4: Create a pointer variable, and ask the engine for our active online subsystem implementation
	// This will return the subsystem that is currently being used (like Steam)
	// This if-statement also makes sure that the subsystem is valid
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		// IOnlineSubsystem exposes service interfaces such as session, identity, friends, achievements, etc.
		// IOnlineSession is specifically the session interface that implements session-related APIs such as
		// create/join/find/destroy sessions
		SessionInterface = SubSystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			// Step 6: Bind delegates. Delegates are essentially events
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UTutorialGameInstance::OnCreateSessionComplete);

			//UE_LOG(LogTemp, Warning, TEXT("Online Subsystem found: %s"), *SubSystem->GetSubsystemName().ToString());
		}
	}
}

// Step 5: Define functions for creating/joining a session
// Go back to Unreal Editor to attach these functions to the buttons in our main menu
void UTutorialGameInstance::CreateServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating server..."));

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = true;	// True for testing, false for Steam
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 4;

	SessionInterface->CreateSession(0, FName("New Session"), SessionSettings);
}

void UTutorialGameInstance::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining server..."));
}

// Step 6: What happens when a session is created
void UTutorialGameInstance::OnCreateSessionComplete(FName ServerName, bool IsSuccessful)
{
	// 0 indicates failure, 1 indicates success
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete - success? %d"), IsSuccessful);

	// Server travel if successful
	if (IsSuccessful)
	{
		// Get the level path by right-clicking on a level in Unreal Editor and selecting "Copy Reference"
		// Remove anything before /Game and anything after the period near the end of the path
		// Add ?listen to indicate that this is a listen server
		FString LevelRef = "/Game/_TUTORIALS/OnlineSubsystem/OnlineSubsystemTutorial?listen";

		GetWorld()->ServerTravel(LevelRef);
	}
}