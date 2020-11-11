// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTest.h"

// Sets default values
ACustomTest::ACustomTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

