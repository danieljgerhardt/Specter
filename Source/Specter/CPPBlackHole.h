// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPBlackHole.generated.h"

UCLASS()
class SPECTER_API ACPPBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPBlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Black Hole")
	FRotator RotationDirection{ 0.0f, 0.0f, 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Black Hole")
	float PullForce{ 10000.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Black Hole")
	float AffectingDistance{ 1000.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Black Hole")
	float RotationForce{ 2000.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Black Hole")
	TArray<AActor*> AffectedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componets")
	class UStaticMeshComponent* BlackHoleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Black Hole")
	bool AffectsPlayer{ true };

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* IntersectionSphere;

	void GetActorsWithCharacterMovement();

};
