// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MiSoGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FCreateServerInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString serverName;
	UPROPERTY(BlueprintReadWrite)
		FString hostName;
	UPROPERTY(BlueprintReadWrite)
		bool isLan;
};

USTRUCT(BlueprintType)
struct FServerInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		FString serverName;
	UPROPERTY(BlueprintReadOnly)
		FString hostName;
	UPROPERTY(BlueprintReadOnly)
		int32 currPlayers;
	UPROPERTY(BlueprintReadOnly)
		FString playerCount;
	UPROPERTY(BlueprintReadOnly)
		int32 serverArrIndex;
	UPROPERTY(BlueprintReadOnly)
		bool isLan;
	UPROPERTY(BlueprintReadOnly)
		int32 ping;
	UPROPERTY(BlueprintReadOnly)
		bool hasStarted;

	void setPlayerCount()
	{
		playerCount = FString(FString::FromInt(currPlayers));
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerDel, FServerInfo,  serverListDel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerSeachedDel, bool, SearchForServer);

/**
 * 
 */
UCLASS()
class MISOMADNESS_API UMiSoGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
//Constructor
	UMiSoGameInstance();

protected:
	FName MySessionName;

	UPROPERTY(BlueprintAssignable)
		FServerDel serverListDel;
	UPROPERTY(BlueprintAssignable)
		FServerSeachedDel SearchForServer;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	virtual void Init() override;
	//when create session is complete call this function
	virtual void OnCreateSessionComplete(FName SessionName, bool isSuccessful);
	//when find session is complete call this function
	virtual void OnFindSessionComplete(bool isSuccessful);
	//when join session is complete call this function
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type result);
	//when destroy the session
	virtual void OnDestroySessionComplete(FName SessionName, bool isSuccessful);

	UFUNCTION(BlueprintCallable)
		void HostServer(FCreateServerInfo createServerInfo);
	UFUNCTION(BlueprintCallable)
		void FindServerList();
	UFUNCTION(BlueprintCallable)
		void JoinServerList(int32 arrayIndex);
	UFUNCTION(BlueprintCallable)
		void HostGameStart(FServerInfo serverInfo);
	UFUNCTION(BlueprintCallable)
		void LeaveServer();
};
