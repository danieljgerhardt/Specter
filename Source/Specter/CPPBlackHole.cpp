#include "CPPBlackHole.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACPPBlackHole::ACPPBlackHole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the sphere component
	IntersectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	IntersectionSphere->SetupAttachment(RootComponent);

	BlackHoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHoleMesh"));
	BlackHoleMesh->SetupAttachment(IntersectionSphere);
	BlackHoleMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/LevelObjects/Sphere.Sphere'")).Object);

	BlackHoleMesh->SetVisibility(true);
	BlackHoleMesh->SetHiddenInGame(false);

}

// Called when the game starts or when spawned
void ACPPBlackHole::BeginPlay()
{
	Super::BeginPlay();

	IntersectionSphere->SetSphereRadius(AffectingDistance);

}

// Called every frame
void ACPPBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetActorsWithCharacterMovement();

	for (AActor* Actor : AffectedActors) {
		FVector ActorLocation = Actor->GetActorLocation();
		FVector BlackHoleLocation = GetActorLocation();
		FVector PullDirection = (BlackHoleLocation - ActorLocation).GetSafeNormal();
		float DistToActor = (BlackHoleLocation - ActorLocation).Size();
		if (DistToActor > AffectingDistance) {
			continue;
		}

		UCharacterMovementComponent* CharacterMovement = Actor->FindComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovement) {
			//apply pull force
			float DistanceScale = (PullForce - DistToActor);
			FVector IterPullForce = PullDirection * DistanceScale;
			CharacterMovement->AddImpulse(IterPullForce * DeltaTime, true);

			//apply rotation force
			FRotator UpdatedRotation = GetActorRotation() + RotationDirection;
			FVector IterRotationDirection = FVector::CrossProduct(UKismetMathLibrary::GetUpVector(RotationDirection), PullDirection);
			FVector IterRotationForce = IterRotationDirection.GetSafeNormal() * RotationForce;
			CharacterMovement->AddImpulse(IterRotationForce * DeltaTime, true);
			SetActorRotation(UpdatedRotation);
		}
	}
}

void ACPPBlackHole::GetActorsWithCharacterMovement()
{
	TArray<AActor*> OverlappingActors;
	IntersectionSphere->GetOverlappingActors(OverlappingActors);

	AffectedActors.Empty();
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->FindComponentByClass<UCharacterMovementComponent>())
		{
			AffectedActors.Add(Actor);
		}
	}
}