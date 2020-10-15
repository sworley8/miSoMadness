// Fill out your copyright notice in the Description page of Project Settings.


#include "BridgeItem.h"

// Sets default values
ABridgeItem::ABridgeItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
}


void ABridgeItem::ChangeMesh(UStaticMesh* NewMesh)
{
	StaticMesh->SetStaticMesh(NewMesh);
}

// Called when the game starts or when spawned
void ABridgeItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABridgeItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

