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
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMiSoGameInstance::OnDestroySessionComplete);
		}
	}
}

void UMiSoGameInstance::OnCreateSessionComplete(FName SessionName, bool isSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("OnStartingSessionComplete, Success: %d"), isSuccessful);
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->StartSession(SessionName)
		}
	}


}

void UMiSoGameInstance::OnStartSessionComplete(FName SessionName, bool isSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("OnStartingSessionComplete, Success: %d"), isSuccessful);
	if (isSuccessful)
	{
		//UGameplayStatics::OpenLevel(GetWorld(), "RunMap", true, "listen");
		GetWorld()->ServerTravel("/Game/ThirdPersonBP/Maps/RunMap?listen");
	}

}

void UMiSoGameInstance::OnDestroySessionComplete(FName SessionName, bool isSuccessful)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnDestroySessionComplete, Success: %d"), isSuccessful);
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnDestroying, Success: %d"), isSuccessful);
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			if (isSuccessful)
			{
				UE_LOG(LogTemp, Warning, TEXT("OnDestroySessionComplete, Success: %d"), isSuccessful);
				//UGameplayStatics::OpenLevel(GetWorld(), "RunMap", true, "listen");
				GetWorld()->ServerTravel("/Game/ThirdPersonBP/Maps/MainRoomMap?listen");
			}
		}
	}
}

void UMiSoGameInstance::OnFindSessionComplete(bool isSuccessful)
{
	SearchForServer.Broadcast(false);
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete, Success: %d"), isSuccessful);
	if (isSuccessful)
	{
		int32 arrIndex = -1;
		for (FOnlineSessionSearchResult result : SessionSearch->SearchResults)
		{
			++arrIndex;
			if (!result.IsValid())
			{
				continue;
			}
			FServerInfo serverInfo;
			FString ServerName = "Not a Mi So Madness Game";
			FString HostName = "Not a Mi So Madness Host";
			result.Session.SessionSettings.Get(FName("SERVER_NAME_KEY"), ServerName);
			result.Session.SessionSettings.Get(FName("SERVER_HOST_KEY"), HostName);
			serverInfo.serverName = ServerName;
			serverInfo.hostName = HostName;
			//UE_LOG(LogTemp, Warning, TEXT(serverInfo));
			serverInfo.currPlayers = (1000 - result.Session.NumOpenPublicConnections);
			serverInfo.serverArrIndex = arrIndex;
			serverInfo.setPlayerCount();
			serverInfo.isLan = result.Session.SessionSettings.bIsLANMatch;
			if (serverInfo.isLan) {
				serverInfo.ping = result.PingInMs;
			} else {
				serverInfo.ping = 666
			}

			serverListDel.Broadcast(serverInfo);
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
		{
			UE_LOG(LogTemp, Warning, TEXT("SteamHostWorks"));
			player->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}

	}
}

void UMiSoGameInstance::HostServer(FCreateServerInfo createServerInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));
	FOnlineSessionSettings sessionSettings;
	sessionSettings.bAllowJoinInProgress = true;
	sessionSettings.bIsDedicated = false;
	sessionSettings.bAllowJoinViaPresence = true;
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
		UE_LOG(LogTemp, Warning, TEXT("Join Server Works at spot: %d"), arrayIndex);
		SessionInterface->JoinSession(0, MySessionName, result);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Join Server Not Works: %d"), arrayIndex);
	}
}

void UMiSoGameInstance::HostGameStart(FServerInfo serverInfo)
{

	FOnlineSessionSettings sessionSettings;
	if (serverInfo.hasStarted)
	{
		sessionSettings.bAllowJoinInProgress = false;
		sessionSettings.bAllowJoinViaPresence = false;
	}
}

void UMiSoGameInstance::LeaveServer()
{
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Destroy Server Works: %s"), ExistingSession);
			auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
			SessionInterface->DestroySession(ExistingSession);
		}
	}

}
