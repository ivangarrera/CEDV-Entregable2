#include "LeftRightSlugEnemy.h"
#include "EngineMinimal.h"
#include "Engine.h"

ALeftRightSlugEnemy::ALeftRightSlugEnemy() : Super(), bGoRight(true), AccumulatedMovementTime(0.f)
{
	TWeakObjectPtr<UMaterialInstanceDynamic> Material = SkeletalMesh->CreateAndSetMaterialInstanceDynamic(0);
	Material->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(1.f, 1.f, 0.f));

	// Unblock the rotation and translation in X and Y axis.
	SkeletalMesh->BodyInstance.bLockXRotation = false;
	SkeletalMesh->BodyInstance.bLockYRotation = false;
	SkeletalMesh->BodyInstance.bLockXTranslation = false;
	SkeletalMesh->BodyInstance.bLockYTranslation = false;

}

void ALeftRightSlugEnemy::RunBehaviour(float DeltaTime)
{
	AccumulatedMovementTime += DeltaTime;

	// Cast a ray from the enemy to the ground, to know if he stands on the ground or not
	float Offset = 1.0f;
	FHitResult HitResult;
	FVector Start = GetActorLocation() + (GetActorUpVector() * Offset); 
	FVector End = Start + (-1 * GetActorUpVector() * 50.f);
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bTraceComplex = true;
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, TraceParams);
	if (Hit) 
	{
		// If it's on the ground, its linear velocity must be zero
		SkeletalMesh->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
		//SkeletalMesh->SetPhysicsAngularVelocity(FVector(0.f, 0.f, 0.f));
	}


	if (bGoRight)
	{
		float NewXPosition = GetActorLocation().X + Speed;
		SetActorLocation(FVector(NewXPosition, GetActorLocation().Y, GetActorLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
	}
	else
	{
		float NewXPosition = GetActorLocation().X - Speed;
		SetActorLocation(FVector(NewXPosition, GetActorLocation().Y, GetActorLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
	}

	// Spawn the projectiles
	if (AccumulatedDeltaTime >= FireTimeInterval)
	{
		FVector Location = GetActorLocation() + GetActorForwardVector() * 250.f;
		FRotator Rotation = GetActorRotation();
		GetWorld()->SpawnActor(ProjectileClass, &Location, &Rotation);
	}

	// Change direction each FireTimeInterval seconds.
	if (AccumulatedDeltaTime >= FireTimeInterval)
	{
		bGoRight = !bGoRight;
		AccumulatedDeltaTime = 0.f;
	}
}


