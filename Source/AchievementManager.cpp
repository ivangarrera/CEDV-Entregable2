#include "AchievementManager.h"
#include "Engine.h"

// Sets default values
AAchievementManager::AAchievementManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAchievementManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAchievementManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAchievementManager::KillAllEnemiesWithoutHarm()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("YOU KILLED ALL ENEMIES WHITHOUT HARM")));
	}
}

void AAchievementManager::KillAllEnemiesWithoutMissingShots()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("YOU KILLED ALL ENEMIES WITHOUT MISSING SHOTS")));
	}
}

void AAchievementManager::KillNEnemiesOfAType(int NumberOfEnemies, FString EnemyType)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("YOU KILLED %d "), NumberOfEnemies) + EnemyType);
	}
}