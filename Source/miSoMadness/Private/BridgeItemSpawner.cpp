// Fill out your copyright notice in the Description page of Project Settings.


#include "BridgeItemSpawner.h"

// Sets default values
ABridgeItemSpawner::ABridgeItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //doesn't matter since i'm going to convert this back into a bridgegamemode eventually anyway
}

// Called when the game starts or when spawned
void ABridgeItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnRandomBridgeItems(4); //just here as a simple test for now
}

// Called every frame
void ABridgeItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABridgeItemSpawner::SpawnBridgeItem(UStaticMesh* SpawnMesh, FVector SpawnLocation, FRotator SpawnRotation)
{
	FActorSpawnParameters SpawnParameters;
	ABridgeItem* SpawnedBridgeItem = GetWorld()->SpawnActor<ABridgeItem>(ABridgeItem::StaticClass(), SpawnLocation, SpawnRotation, SpawnParameters);
	SpawnedBridgeItem->ChangeMesh(SpawnMesh);
	BridgeItems.Add(SpawnedBridgeItem);
}

void ABridgeItemSpawner::SpawnRandomBridgeItems(int32 NumberOfItems) //Spawns BridgeItems so that there is an even balance of mesh diversity
{
	while (NumberOfItems > 0)
	{
		TArray<UStaticMesh*> MeshesCopy (BridgeItemMeshes); 
		int32 Iterations = FMath::Min(MeshesCopy.Num(), NumberOfItems);
		for (int32 i = 0; i < Iterations; i++)
		{
			int32 Index = FMath::RandRange(0, MeshesCopy.Num() - 1);
			SpawnBridgeItem(MeshesCopy[Index], FVector(0, 0, 0), FRotator(0, 0, 0)); //Currently spawns everything in the same place and at the same time
			MeshesCopy.RemoveAt(Index);
		}
		NumberOfItems -= Iterations;
	}
}

