#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "RandomMovementSlugEnemy.generated.h"

UCLASS()
class CPPINHERITANCE_API ARandomMovementSlugEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& transform) override;

public:
	ARandomMovementSlugEnemy();

private:
	float Velocity;
	FVector NewPosition;
	TWeakObjectPtr<AActor> ReferencePlane;

	void RunBehaviour(float DeltaTime) override;
	FVector GetRandomPoint();
};
