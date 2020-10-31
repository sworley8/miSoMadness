// Fill out your copyright notice in the Description page of Project Settings.


#include "BridgeItemSpawner.h"

// Sets default values
ABridgeItemSpawner::ABridgeItemSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	UClass* TempItemsList[] = {ABridgeItem::StaticClass()}; 
	ItemList.Append(TempItemsList, UE_ARRAY_COUNT(TempItemsList));
	//ItemList.Add(ABridgeItem::StaticClass());

}

// Called when the game starts or when spawned
void ABridgeItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnRandomItems(1); //just here as a simple test for now
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
			int32 Index = FMath::RandRange(0, ItemListCopy.Num() - 1);
			SpawnItem(ItemListCopy[Index], FVector(0, 0, 200), FRotator(0, 0, 0)); //Currently spawns everything in the same place and at the same time
			ItemListCopy.RemoveAt(Index);
		}
		NumberOfItems -= Iterations;
	}
}

