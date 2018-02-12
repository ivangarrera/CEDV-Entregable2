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
#include "BaseEnemy.generated.h"

// (1)
// UE4 does not support abstract classes by default, using C++ regular
// syntax. In order to accomplish it, UE4 provides the UCLASS(abstract) macro ...
UCLASS(Abstract)
class CPPINHERITANCE_API ABaseEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		TWeakObjectPtr<UAnimSequence> IdleAnimation;
	UPROPERTY()
		TWeakObjectPtr<UParticleSystem> ExplosionParticleSystem;

protected:
	UFUNCTION()
		virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	// (2) 
	// ... so, in order to create pure virtual functions (i.e., functions that
	// must be implemented in child classes), UE4 provides the PURE_VIRTUAL(function, default_code)
	// macro. Watch out for the mandatory comma!
	virtual void RunBehaviour(float DeltaTime) PURE_VIRTUAL(ABaseEnemy::RunBehaviour, );

	UPROPERTY()
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	TSubclassOf<AActor> ProjectileClass;
	TWeakObjectPtr<APawn> PlayerPawn;

	UPROPERTY()
	TWeakObjectPtr<class AEnemyManager> EnemyManager;

	float AccumulatedDeltaTime;

	float const FireTimeInterval = 2.0f;
};
