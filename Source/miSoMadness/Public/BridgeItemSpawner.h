// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "BridgeItem.h"
#include "BridgeItemSpawner.generated.h"

UCLASS()
class MISOMADNESS_API ABridgeItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABridgeItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnItem(UClass* SpawnItemClass, FVector SpawnLocation, FRotator SpawnRotation);
	void SpawnRandomItems(int32 NumberOfItems);
	void CleanUp();

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Arrays") //TArray of all the bridge items that have a chance to spawn
	TArray<UClass*> ItemList;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Arrays") //TArray of all the bridge items that have been instantiated (for cleanup purposes)
	TArray<AActor*> CurrentItems;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Spawn Location") //Center of rectangle where items shall be spawned
	FVector SpawnCenter; 

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Spawn Location") //X distance from center to rectangle's edge
	int32 SpawnRangeX;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Spawn Location") //Y distance from center to rectangle's edge
	int32 SpawnRangeY;
};
