// Fill out your copyright notice in the Description page of Project Settings.

#include "miSoMadness/Public/MiSoGameInstance.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "OnlineSessionSettings.h"

UMiSoGameInstance::UMiSoGameInstance()
{
	MySessionName = FName("MySession");
}
void UMiSoGameInstance::Init()
{
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			//Bind Delegates here
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMiSoGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMiSoGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMiSoGameInstance::OnJoinSessionComplete);
		}
	}
}

void UMiSoGameInstance::OnCreateSessionComplete(FName SessionName, bool isSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, Success: %d"), isSuccessful);
	if (isSuccessful)
	{
		GetWorld()->ServerTravel("/Game/ThirdPersonBP/Maps/RunMap?listen");
	}
}

void UMiSoGameInstance::OnFindSessionComplete(bool isSuccessful)
{
	SearchForServer.Broadcast(false);
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete, Success: %d"), isSuccessful);
	if (isSuccessful)
	{
		int8 arrIndex = 0;
		for (FOnlineSessionSearchResult result : SessionSearch->SearchResults)
		{
			if (!result.IsValid())
			{
				continue;
			}
			FServerInfo serverInfo;
			FString ServerName = "Testing Server Name";
			FString HostName = "Testing Host Name";
			result.Session.SessionSettings.Get(FName("SERVER_NAME_KEY"), ServerName);
			result.Session.SessionSettings.Get(FName("SERVER_HOST_KEY"), HostName);
			serverInfo.serverName = ServerName;
			serverInfo.currPlayers = result.Session.NumOpenPublicConnections;
			serverInfo.serverArrIndex = arrIndex;
			serverInfo.setPlayerCount();
			serverInfo.isLan = result.Session.SessionSettings.bIsLANMatch;
			serverInfo.ping = result.PingInMs;

			serverListDel.Broadcast(serverInfo);
			++arrIndex;
		}
		UE_LOG(LogTemp, Warning, TEXT("SearchResult, Sever Count: %d"), SessionSearch->SearchResults.Num());
		// if (SessionSearch->SearchResults.Num())
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("Joining Server"));
		// 	// SessionInterface->JoinSession(0, "MySession", SearchResult[0]);
		// }

	}
}

void UMiSoGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type result)
{
	if (APlayerController* player = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete, SessionName: %s"), *SessionName.ToString());
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "")
			UE_LOG(LogTemp, Warning, TEXT("ActualWorkedServer"));
			player->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);

	}
}

void UMiSoGameInstance::HostServer(FCreateServerInfo createServerInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));
	FOnlineSessionSettings sessionSettings;
	sessionSettings.bAllowJoinInProgress = true;
	sessionSettings.bIsDedicated = false;
	sessionSettings.bShouldAdvertise = true;
	if (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL" && !createServerInfo.isLan)
	{
		UE_LOG(LogTemp, Warning, TEXT("SteamHostWorks"));
		sessionSettings.bIsLANMatch = false;
	}
	else {
		sessionSettings.bIsLANMatch = true;
	}
	sessionSettings.bUsesPresence = true;
	sessionSettings.NumPublicConnections = 1000;

	sessionSettings.Set(FName("SERVER_NAME_KEY"), createServerInfo.serverName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	sessionSettings.Set(FName("SERVER_HOST_KEY"), createServerInfo.hostName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionInterface->CreateSession(0, MySessionName, sessionSettings);
}

void UMiSoGameInstance::FindServerList()
{
	SearchForServer.Broadcast(true);
	UE_LOG(LogTemp, Warning, TEXT("FindServerList"));
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL")
	{
		UE_LOG(LogTemp, Warning, TEXT("SteamJoinWorks"));
		SessionSearch->bIsLanQuery = false;
	}
	else {
		SessionSearch->bIsLanQuery = true;
	}
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());

}

void UMiSoGameInstance::JoinServerList(int32 arrayIndex)
{
	FOnlineSessionSearchResult result = SessionSearch->SearchResults[arrayIndex];
	if (result.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Join Server Works: %d"), arrayIndex);
		SessionInterface->JoinSession(0, MySessionName, result);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Join Server Not Works: %d"), arrayIndex);
	}
}

void UMiSoGameInstance::HostGameStart()
{

}