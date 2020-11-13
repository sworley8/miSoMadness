// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PowerUp.generated.h"
#include "RamenCharacter.h"

UCLASS()
class MISOMADNESS_API APowerUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Components")
	USphereComponent* PickupCollisionSphere;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Components")
	float SphereRadius;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Components")
	float RotationSpeed;

	UFUNCTION(Blueprintable)
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
