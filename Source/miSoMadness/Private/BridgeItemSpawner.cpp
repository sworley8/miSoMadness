// Fill out your copyright notice in the Description page of Project Settings.


#include "BridgeItemSpawner.h"

// Sets default values
ABridgeItemSpawner::ABridgeItemSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	UClass* TempItemList[] = {ABridgeItem::StaticClass()}; //replace ABridgeItem with the desired actor(s) -- always followed by ::StaticClass()
	ItemList.Append(TempItemList, UE_ARRAY_COUNT(TempItemList));
}

// Called when the game starts or when spawned
void ABridgeItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnRandomItems(5); //just here as a simple test for now
}

// Called every frame
void ABridgeItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABridgeItemSpawner::SpawnItem(UClass* SpawnItemClass, FVector SpawnLocation, FRotator SpawnRotation)
{
	FActorSpawnParameters SpawnParameters;
	AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(SpawnItemClass, SpawnLocation, SpawnRotation, SpawnParameters);
	CurrentItems.Add(SpawnedItem);
}

void ABridgeItemSpawner::SpawnRandomItems(int32 NumberOfItems) //Spawns items with beautiful  d i v e r s i t y
{
	while (NumberOfItems > 0)
	{
		TArray<UClass*> ItemListCopy (ItemList); 
		int32 Iterations = FMath::Min(ItemListCopy.Num(), NumberOfItems);
		for (int32 i = 0; i < Iterations; i++)
		{
			FVector SpawnLocation;
			SpawnLocation.X = SpawnCenter.X + FMath::RandRange(-SpawnRangeX, SpawnRangeX);
			SpawnLocation.Y = SpawnCenter.Y + FMath::RandRange(-SpawnRangeY, SpawnRangeY);
			SpawnLocation.Z = SpawnCenter.Z;

			int32 Index = FMath::RandRange(0, ItemListCopy.Num() - 1);
			SpawnItem(ItemListCopy[Index], SpawnLocation, FRotator(0, 0, 0));
			ItemListCopy.RemoveAt(Index);
		}
		NumberOfItems -= Iterations;
	}
}

void ABridgeItemSpawner::CleanUp() //for when bridgebuilding is over. cleans up all of the spawned actors and resets the array, probably ^TM
{
	for (AActor* item : CurrentItems)
	{
		item->Destroy();
	}
	CurrentItems.Empty();
}
