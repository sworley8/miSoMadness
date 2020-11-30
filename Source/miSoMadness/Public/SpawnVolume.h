// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"
#include "SpawnVolume.generated.h"


UCLASS()
class MISOMADNESS_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// whereToSpawn getter method
	FORCEINLINE class UBoxComponent* getWhereToSpawn() const { return whereToSpawn; }

	void createPlayerStart();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", Meta = (AllowPrivateAccess = "True"))
		class UBoxComponent *whereToSpawn;

	UPROPERTY(EditAnywhere)
		int32 spawnLocationXRange;
	UPROPERTY(EditAnywhere)
		int32 spawnLocationYRange;
	UPROPERTY(EditAnywhere)
		int32 playerStartDistance;

	int32 playerNum;
	FVector spawnLocation;
	TSet<FVector> spawnLocationsSet;
};
