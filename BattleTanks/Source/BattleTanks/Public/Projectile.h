// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void LaunchProjectile(float);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

private:	
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UProjectileMovementComponent* projectileMovementComponent = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* projectileCollisionMesh = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* projectileLaunchBlast = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* projectileImpactBlast = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* projectileExplosionForce = NULL;

	UPROPERTY(EditDefaultsOnly, Category = "Timer")
		float delay = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float damage = 30.f;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();



	
	
};
