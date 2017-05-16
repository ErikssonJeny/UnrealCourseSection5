// Copyright Erik Jeny 2017-2018

#pragma once

#include "../Public/Projectile.h"
#include "ProjectileLaser.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API AProjectileLaser : public AActor
{
	GENERATED_BODY()
	
public:
	AProjectileLaser();
	void LaunchProjectile(float);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UProjectileMovementComponent* projLasMovementComponent = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* projLasCollisionMesh = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* projLasLaunchBlast = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* projLasImpactBlast = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UAudioComponent* projLasLaunchSound = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UAudioComponent* projLasImpactSound = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* projLasExplosionForce = NULL;

	UPROPERTY(EditDefaultsOnly, Category = "Timer")
		float deathDelay = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float projectileDamage = 30.f;

	UFUNCTION()
		void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	void OnTimerExpire();
	
	
	
};
