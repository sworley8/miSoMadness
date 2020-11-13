// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "DrawDebugHelpers.h"

// Sets default values
APowerUp::APowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 125.0f; //might want to make this slightly larger
	RotationSpeed = 1.0f;

	PickupCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	PickupCollisionSphere->InitSphereRadius(SphereRadius);
	PickupCollisionSphere->SetCollisionProfileName("Trigger");
	SetRootComponent(PickupCollisionSphere);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Binaries/3D/chips.chips'")); //should disable collision for the mesh itself? since overlap detected by sphere. but idk how to do that
	StaticMesh->SetStaticMesh(MeshAsset.Object);
	StaticMesh->SetupAttachment(RootComponent);

	PickupCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnPlayerOverlap);

}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = GetActorRotation().Add(0, RotationSpeed, 0); 
	SetActorRotation(NewRotation);
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Purple, false, -1, 0, 1); //shows hitbox for powerup
}

void APowerUp::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) /*&& (OtherActor->IsA(APlayerClass::StaticClass())*/ && (OtherComponent != nullptr))
	{
		


		Destroy();
	}
}