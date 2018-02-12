#include "ChangeColorSlugEnemy.h"
#include "EngineMinimal.h"

AChangeColorSlugEnemy::AChangeColorSlugEnemy() : Super(), ChangeColorTime(1.f), AccumulatedChangeColorTime(0.f)
{
	Material = SkeletalMesh->CreateAndSetMaterialInstanceDynamic(0);
	Material->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(1.f, 1.f, 1.f));
}

void AChangeColorSlugEnemy::RunBehaviour(float DeltaTime)
{
	AccumulatedChangeColorTime += DeltaTime;

	if (AccumulatedChangeColorTime >= ChangeColorTime)
	{
		FLinearColor NewColor = Material->K2_GetVectorParameterValue(FName(TEXT("Color")));
		NewColor.R = FMath::RandRange(0.f, 1.f);
		NewColor.G = FMath::RandRange(0.f, 1.f);
		NewColor.B = FMath::RandRange(0.f, 1.f);
		Material->SetVectorParameterValue(FName(TEXT("Color")), NewColor);
		AccumulatedChangeColorTime = 0.f;
	}

	// Spawn the projectiles
	if (AccumulatedDeltaTime >= FireTimeInterval)
	{
		FVector Location = GetActorLocation() + GetActorForwardVector() * 250.f;
		FRotator Rotation = GetActorRotation();
		GetWorld()->SpawnActor(ProjectileClass, &Location, &Rotation);
		AccumulatedDeltaTime = 0.f;
	}
}
