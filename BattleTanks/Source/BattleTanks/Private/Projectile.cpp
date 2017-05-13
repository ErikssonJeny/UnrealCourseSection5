// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	projectileMovementComponent->bAutoActivate = false;

	projectileCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	SetRootComponent(projectileCollisionMesh);
	projectileCollisionMesh->SetNotifyRigidBodyCollision(true);
	projectileCollisionMesh->SetVisibility(false);

	projectileLaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Component"));
	projectileLaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	projectileImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast Component"));
	projectileImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	projectileImpactBlast->bAutoActivate = false;

	projectileExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	projectileExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	projectileCollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Projectile hitting."));

	projectileLaunchBlast->Deactivate();
	projectileImpactBlast->Activate();
	projectileExplosionForce->FireImpulse();

	SetRootComponent(projectileImpactBlast);
	projectileCollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this, damage, GetActorLocation(), projectileExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectile::OnTimerExpire, delay, false);
}

void AProjectile::LaunchProjectile(float speed)
{
	if (!ensure(projectileMovementComponent))
		return;

	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovementComponent->Activate();
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

