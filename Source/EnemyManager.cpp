#include "EnemyManager.h"
#include "EngineUtils.h"
#include "Engine.h"

#include "BaseEnemy.h"
#include "ShootingSlugEnemy.h"
#include "JumpingShootingSlugEnemy.h"
#include "SuperShootingSlugEnemy.h"
#include "LeftRightSlugEnemy.h"
#include "RandomMovementSlugEnemy.h"
#include "ChangeColorSlugEnemy.h"


// Example of member initialization list
AEnemyManager::AEnemyManager()
	: AccumulatedDeltaTime(0.0f), EnemySpawnTimeSeconds(3.5f), EnemiesSpawned(0), ReferencePlane(0)
{
	PrimaryActorTick.bCanEverTick = true;

	// Store references to enemy classes for later
	EnemyClasses.AddUnique(AShootingSlugEnemy::StaticClass());
	EnemyClasses.AddUnique(AJumpingShootingSlugEnemy::StaticClass());
	EnemyClasses.AddUnique(ASuperShootingSlugEnemy::StaticClass());
	EnemyClasses.AddUnique(ALeftRightSlugEnemy::StaticClass()); 
	EnemyClasses.AddUnique(ARandomMovementSlugEnemy::StaticClass());
	EnemyClasses.AddUnique(AChangeColorSlugEnemy::StaticClass());
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	FString EnemySpawnPlaneString = FString(TEXT("EnemySpawnPlane"));

	// Get a reference to the invisible plane used to spawn enemies
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (EnemySpawnPlaneString.Equals(ActorItr->GetName()))
		{
			// Conversion to smart pointer
			ReferencePlane = *ActorItr;
			break;
		}
	}

	// Get a reference to the AchievementManager
	for (TActorIterator<AActor> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		if (Iterator->GetName().Contains(FString(TEXT("AchievementManager"))))
		{
			AchievementManager = Cast<AAchievementManager>(*Iterator);
			break;
		}
	}

	// Get a reference to FirstPersonCharacter
	Character = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Iterate over the EnemiesKilled to check if the achievement of killing n enemies of a type is met.
	for (auto& Elem : ABaseEnemy::EnemiesKilled)
	{
		if (Elem.Value >= 2)
		{
			AchievementManager->KillNEnemiesOfAType(Elem.Value, Elem.Key.Get()->GetName());
		}
	}

	AccumulatedDeltaTime += DeltaTime;
	if ((AccumulatedDeltaTime >= EnemySpawnTimeSeconds)
		&&
		(GetNumberOfEnemies() < MaxNumberOfEnemies)
		&&
		(EnemiesSpawned < TotalEnemies))
	{
		// Spawn new enemy and reset the counter
		SpawnEnemy();
		EnemiesSpawned++;
		AccumulatedDeltaTime = 0.0f;
	}

	// Look if Character have been shooted, when all enemies have been killed
	if (Character.Get() 
		&& EnemiesSpawned == TotalEnemies
		&& GetNumberOfEnemies() == 0)
	{
		if (!Character->bIsHit)
		{
			AchievementManager->KillAllEnemiesWithoutHarm();
		}

		// Check if we havn't missed any shot
		if (Character->NumberOfShots <= TotalEnemies)
		{
			AchievementManager->KillAllEnemiesWithoutMissingShots();
		}
	}
}

int AEnemyManager::GetNumberOfEnemies() const
{
	int LivingEnemies = 0;

	for (TActorIterator<ABaseEnemy> ActorItr(GetWorld(), ABaseEnemy::StaticClass()); ActorItr; ++ActorItr)
	{
		LivingEnemies++;
	}

	return LivingEnemies;
}

FVector AEnemyManager::GetRandomLocationFromReferencePlane() const
{
	FVector RandomLocation;
	FVector Orgin;
	FVector BoundsExtent;
	ReferencePlane->GetActorBounds(false, Orgin, BoundsExtent);

	// Build a bounding box and get a random location.
	RandomLocation = FMath::RandPointInBox(FBox::BuildAABB(Orgin, BoundsExtent));

	return RandomLocation;
}

TSubclassOf<ABaseEnemy> AEnemyManager::GetRandomEnemyClass() const
{
	return EnemyClasses[FMath::RandRange(0, EnemyClasses.Num() - 1)];
}

void AEnemyManager::SpawnEnemy()
{
	
	TSubclassOf<ABaseEnemy> EnemyType = GetRandomEnemyClass();
	FVector EnemySpawnLocation = GetRandomLocationFromReferencePlane();
	GetWorld()->SpawnActor(EnemyType, &EnemySpawnLocation);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("Number of Enemies: %d"), GetNumberOfEnemies()));
	}
}
