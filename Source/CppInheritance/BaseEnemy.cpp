#include "BaseEnemy.h"

// This file includes most of UE4 libraries, 
// so you don't have to manually import header files individually ...
#include "EngineMinimal.h"
#include "Engine.h"
#include "EnemyManager.h"

// ... but PhysicsAsset library is not included by default, so we include it
#include "PhysicsEngine/PhysicsAsset.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Models/Slug/Mesh/slug.slug'"));
	if (MeshAsset.Succeeded())
	{
		SkeletalMesh->SetSkeletalMesh(MeshAsset.Object);
		SkeletalMesh->SetWorldScale3D(FVector(50.0f, 50.0f, 50.0f));
		SkeletalMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	}

	auto PhysicsAsset = ConstructorHelpers::FObjectFinder<UPhysicsAsset>(TEXT("PhysicsAsset'/Game/Models/Slug/Mesh/slug_PhysicsAsset.slug_PhysicsAsset'"));
	if (PhysicsAsset.Succeeded())
	{
		SkeletalMesh->SetPhysicsAsset(PhysicsAsset.Object);
		SkeletalMesh->SetSimulatePhysics(true);
		SkeletalMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
		SkeletalMesh->BodyInstance.bLockXRotation = true;
		SkeletalMesh->BodyInstance.bLockYRotation = true;
		SkeletalMesh->BodyInstance.bLockXTranslation = true;
		SkeletalMesh->BodyInstance.bLockYTranslation = true;
	}

	auto AnimAsset = ConstructorHelpers::FObjectFinder<UAnimSequence>(TEXT("AnimSequence'/Game/Models/Slug/Mesh/slug_Anim_Idle.slug_Anim_Idle'"));
	if (AnimAsset.Succeeded())
	{
		IdleAnimation = AnimAsset.Object;
	}

	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));
	if (ParticleSystemAsset.Succeeded())
	{
		ExplosionParticleSystem = ParticleSystemAsset.Object;
	}

	OnActorHit.AddDynamic(this, &ABaseEnemy::OnHit);
	auto FirstPersonProjectileBPClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("/Game/Blueprints/FirstPersonProjectile"));
	if (FirstPersonProjectileBPClass.Succeeded()) {
		ProjectileClass = FirstPersonProjectileBPClass.Class;
	}
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	SkeletalMesh->PlayAnimation(IdleAnimation.Get(), true);
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Get a reference to Enemy Manager
	FString EnemyManagerText = FString(TEXT("EnemyManager"));
	for (TActorIterator<AActor> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		if (Iterator->GetName().Contains(EnemyManagerText))
		{
			EnemyManager = Cast<AEnemyManager>(*Iterator);
			break;
		}
	}
}

void ABaseEnemy::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AccumulatedDeltaTime += DeltaTime;

	// The common behaviour for all enemies will be to rotate them to face the player
	FRotator EnemyRotation = FRotationMatrix::MakeFromX(PlayerPawn->GetActorLocation() - GetActorLocation()).Rotator();
	SkeletalMesh->SetRelativeRotation(EnemyRotation, false, nullptr, ETeleportType::TeleportPhysics);

	// Run the specific behaviour of the child classes through polymorphic calling
	RunBehaviour(DeltaTime);
}

void ABaseEnemy::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor) {
		if (OtherActor->IsA(ProjectileClass)) {
			EnemyManager->EnemyDestroyed(SelfActor);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);
			Destroy();
		}
	}
}
