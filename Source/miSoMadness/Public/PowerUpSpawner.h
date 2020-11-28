// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PowerUp.h"
#include "PowerUpSpawner.generated.h"

UCLASS()
class MISOMADNESS_API APowerUpSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APowerUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnRandomPowerUp();
	void CleanUp();
	static bool IsValid(AActor* Actor);

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables") //TArray of all the powerups that have a chance to spawn
	TArray<UClass*> PowerUpList;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables")
	AActor* SpawnedPowerUp;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables")
	float PowerUpRespawnTime;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Variables")
	float RespawnTimer;

};
