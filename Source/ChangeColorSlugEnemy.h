#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "ChangeColorSlugEnemy.generated.h"


UCLASS()
class CPPINHERITANCE_API AChangeColorSlugEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	AChangeColorSlugEnemy();

private:
	float ChangeColorTime;
	float AccumulatedChangeColorTime;

	TWeakObjectPtr<UMaterialInstanceDynamic> Material;

	void RunBehaviour(float DeltaTime) override;
	
};
