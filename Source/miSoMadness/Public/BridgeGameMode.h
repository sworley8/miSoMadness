// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "BridgeItem.h"
#include "BridgeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MISOMADNESS_API ABridgeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABridgeGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SpawnBridgeItem(UStaticMesh* SpawnMesh, FVector SpawnLocation, FRotator SpawnRotation);
	void SpawnRandomBridgeItems(int32 NumberOfItems);

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Arrays") //TArray of all the static meshes that can be assigned to BridgeItems (current: must be filled manually in editor)
	TArray<UStaticMesh*> BridgeItemMeshes;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Arrays") //TArray of all the BridgeItems that have been instantiated
	TArray<ABridgeItem*> BridgeItems;
};