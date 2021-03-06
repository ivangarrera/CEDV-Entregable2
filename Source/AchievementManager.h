// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.h"
#include "AchievementManager.generated.h"

UCLASS()
class CPPINHERITANCE_API AAchievementManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAchievementManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Functions called when an achievement is achieved
	void KillAllEnemiesWithoutHarm(TWeakObjectPtr<class UTextBlock> TextBlock);
	void KillAllEnemiesWithoutMissingShots(TWeakObjectPtr<class UTextBlock> TextBlock);
	void KillNEnemiesOfAType(TWeakObjectPtr<class UTextBlock> TextBlock, int NumberOfEnemies, FString EnemyType);	
};
