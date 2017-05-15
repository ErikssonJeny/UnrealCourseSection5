// Copyright Erik Jeny 2017-2018

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsteroidDelegate);

UCLASS()
class BATTLETANKS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Asteroid")
		void LaunchAsteroid(float launchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Asteroid")
		void LaunchAsteroidInDirection(float launchSpeed, FVector direction);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
		float initialVelocity = 5;

	UFUNCTION()
		void OnAsteroidDeath();

	UFUNCTION()
		void OnAsteroidScore();


	FAsteroidDelegate OnDeath;
	FAsteroidDelegate OnScore;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
		UStaticMeshComponent* asteroidCollisionMesh = NULL;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
		UProjectileMovementComponent* asteroidMovementComponent = NULL;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
		UParticleSystemComponent* asteroidImpactBlast = NULL;
private:	

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 startingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 currentHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 damageDealt = 100;

	float timeOfDeath;

	bool bCanDie = false;

	float destroyDelay = 1;

	
	
};
