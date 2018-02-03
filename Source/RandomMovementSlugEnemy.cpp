#include "RandomMovementSlugEnemy.h"
#include "EngineMinimal.h"
#include "Engine.h"

ARandomMovementSlugEnemy::ARandomMovementSlugEnemy() : Super(), Velocity(500.f)
{
	NewPosition = FVector(0.f, 0.f, 0.f);

	TWeakObjectPtr<UMaterialInstanceDynamic> Material = SkeletalMesh->CreateAndSetMaterialInstanceDynamic(0);
	Material->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.f, 0.f, 0.f));

	// Unblock the rotation and translation in X and Y axis.
	SkeletalMesh->BodyInstance.bLockXRotation = false;
	SkeletalMesh->BodyInstance.bLockYRotation = false;
	SkeletalMesh->BodyInstance.bLockXTranslation = false;
	SkeletalMesh->BodyInstance.bLockYTranslation = false;
}

void ARandomMovementSlugEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ARandomMovementSlugEnemy::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	// Get a reference to the invisible plane, to generate random points in it
	FString ReferencePlaneString = FString(TEXT("EnemySpawnPlane"));
	if (GetWorld())
	{
		for (TActorIterator<AActor> Iterator(GetWorld()); Iterator; ++Iterator)
		{
			if (ReferencePlaneString.Equals(Iterator->GetName()))
			{
				ReferencePlane = *Iterator;
				break;
			}
		}
	}
}

void ARandomMovementSlugEnemy::RunBehaviour(float DeltaTime)
{
	// Set an initial random point to move the slug
	if (NewPosition.IsZero())
	{
		NewPosition = GetRandomPoint();
	}

	// If the Slug arrives its new position, calculate a new position randomly.
	if (GetActorLocation().Equals(NewPosition, 10.f))
	{
		NewPosition = GetRandomPoint();
	}
	
	// Cast a ray from the enemy to the ground, to know if he stands on the ground or not
	float Offset = 1.0f;
	FHitResult HitResult;
	FVector Start = GetActorLocation() + (GetActorUpVector() * Offset);
	FVector End = Start + (-1 * GetActorUpVector() * 100.f);
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bTraceComplex = true;
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, TraceParams);
	if (Hit)
	{
		// If it's on the ground, its linear velocity must be zero
		SkeletalMesh->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
	}

	// Move from InitialPosition to NewPosition
	FVector Direction = NewPosition - GetActorLocation();
	Direction.Normalize();
	FVector NewLocation = GetActorLocation() + Direction * Velocity * DeltaTime;
	SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);

	// Spawn the projectiles
	if (AccumulatedDeltaTime >= FireTimeInterval)
	{
		FVector Location = GetActorLocation() + GetActorForwardVector() * 250.f;
		FRotator Rotation = GetActorRotation();
		GetWorld()->SpawnActor(ProjectileClass, &Location, &Rotation);
		AccumulatedDeltaTime = 0.f;
	}
}

FVector ARandomMovementSlugEnemy::GetRandomPoint()
{
	FVector Origin;
	FVector BoxExtent;
	ReferencePlane->GetActorBounds(false, Origin, BoxExtent);

	FVector RandomPoint = FMath::RandPointInBox(FBox::BuildAABB(Origin, BoxExtent));
	RandomPoint.Z = 890.f;
	return RandomPoint;
}


