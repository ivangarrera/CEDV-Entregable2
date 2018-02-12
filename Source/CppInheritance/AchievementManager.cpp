#include "AchievementManager.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
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

void AAchievementManager::KillAllEnemiesWithoutHarm(TWeakObjectPtr<UTextBlock> TextBlock)
{
	TextBlock->SetText(FText::FromString(FString("You killed all enemies without suffer harm")));
}

void AAchievementManager::KillAllEnemiesWithoutMissingShots(TWeakObjectPtr<UTextBlock> TextBlock)
{
	TextBlock->SetText(FText::FromString(FString("You killed all enemies without missing shots")));
}

void AAchievementManager::KillNEnemiesOfAType(TWeakObjectPtr<UTextBlock> TextBlock, int NumberOfEnemies, FString EnemyType)
{
	TextBlock->SetText(FText::FromString(FString::Printf(TEXT("You killed %d "), NumberOfEnemies) + EnemyType));
}
