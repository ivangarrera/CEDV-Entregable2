/*********************************************************************
* Module 1. Programming Foundations
* Author: David Vallejo Fernández    David.Vallejo@uclm.es
*         Santiago Sánchez Sobrino   Santiago.Sanchez@uclm.es
*
* You can redistribute and/or modify this file under the terms of the
* GNU General Public License ad published by the Free Software
* Foundation, either version 3 of the License, or (at your option)
* and later version. See <http://www.gnu.org/licenses/>.
*
* This file is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AchievementManager.h"
#include "FirstPersonCharacter.h"
#include "EnemyManager.generated.h"

class ABaseEnemy;


UCLASS()
class CPPINHERITANCE_API AEnemyManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Temporal reference to spawn new enemies
	float AccumulatedDeltaTime;
	float EnemySpawnTimeSeconds;

	// Number of spawned enemies
	int EnemiesSpawned;
	const int MaxNumberOfEnemies = 2;
	const int TotalEnemies = 5;

	// Reference to the AchievementManager
	TWeakObjectPtr<AAchievementManager> AchievementManager;

	// Reference to FirstPersonCharacter
	TWeakObjectPtr<AFirstPersonCharacter> Character;

	// Keeps a list of enemy types to spawn
	TArray<TSubclassOf<ABaseEnemy>> EnemyClasses;

	// Invisible plane to spawn enemies
	TWeakObjectPtr<AActor> ReferencePlane;

	int GetNumberOfEnemies() const;
	FVector GetRandomLocationFromReferencePlane() const;
	TSubclassOf<ABaseEnemy> GetRandomEnemyClass() const;
	void SpawnEnemy();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
