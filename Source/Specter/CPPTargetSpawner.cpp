// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPTargetSpawner.h"

// Sets default values
ACPPTargetSpawner::ACPPTargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPPTargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPPTargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPPTargetSpawner::SpawnTarget(FVector Location)
{
	FRotator Rotation(0.0f, 0.0f, 0.0f); 
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation, SpawnInfo);
}

void ACPPTargetSpawner::InitSpawning(int Count)
{
	FVector Location = GetActorLocation();

	for (int i = 0; i < Count; i++) {
		FVector RandomVec = FMath::VRand();
		RandomVec.X *= static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * SpawnRange.X;
		RandomVec.Y *= static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * SpawnRange.Y;
		RandomVec.Z *= static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * SpawnRange.Z;

		RandomVec += Location;

		SpawnTarget(RandomVec);
	}

	TargetsRemaining = Count;
}

