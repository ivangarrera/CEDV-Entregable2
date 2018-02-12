
#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "LeftRightSlugEnemy.generated.h"


UCLASS()
class CPPINHERITANCE_API ALeftRightSlugEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	ALeftRightSlugEnemy();
	
private:
	const float Speed = 4.f;
	bool bGoRight;
	float AccumulatedMovementTime;
	const float FireTimeInterval = 2.f;

	void RunBehaviour(float DeltaTime) override;

};
