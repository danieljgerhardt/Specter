// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPTargetSpawner.generated.h"

UCLASS()
class SPECTER_API ACPPTargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPTargetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FVector SpawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int TargetsRemaining;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnTarget(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void InitSpawning(int Count);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
