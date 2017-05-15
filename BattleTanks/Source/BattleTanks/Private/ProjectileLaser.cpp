// Copyright Erik Jeny 2017-2018

#include "BattleTanks.h"
#include "../Public/ProjectileLaser.h"

AProjectileLaser::AProjectileLaser()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projLasMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	projLasMovementComponent->bAutoActivate = false;

	projLasCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	SetRootComponent(projLasCollisionMesh);
	projLasCollisionMesh->SetNotifyRigidBodyCollision(true);
	projLasCollisionMesh->SetVisibility(false);

	projLasLaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Component"));
	projLasLaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	projLasImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast Component"));
	projLasImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	projLasImpactBlast->bAutoActivate = false;

	projLasExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	projLasExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectileLaser::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AProjectileLaser::OnOverlap);
}

void AProjectileLaser::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Begin overlap."));

	projLasLaunchBlast->Deactivate();
	projLasImpactBlast->Activate();
	projLasExplosionForce->FireImpulse();

	SetRootComponent(projLasImpactBlast);
	projLasCollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this, projectileDamage, GetActorLocation(), projLasExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectileLaser::OnTimerExpire, deathDelay, false);
}

void AProjectileLaser::LaunchProjectile(float speed)
{
	if (!ensure(projLasMovementComponent))
		return;

	projLasMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projLasMovementComponent->Activate();
}

void AProjectileLaser::OnTimerExpire()
{
	Destroy();
}


