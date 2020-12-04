// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PowerUp.h"
#include "Net/UnrealNetwork.h"
#include "SumoItemSpawner.generated.h"

UCLASS()
class MISOMADNESS_API ASumoItemSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASumoItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnRandomItem();
	void CleanUp();
	static bool IsValid(AActor* Actor);

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables") //TArray of all the SumoItems that have a chance to spawn
	TArray<UClass*> ItemList;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables")
	TArray<AActor*> SpawnedItems;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables")
	float ItemSpawnTime;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables")
	float SpawnTimer;

};
