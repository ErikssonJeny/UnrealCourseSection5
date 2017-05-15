// Copyright Erik Jeny 2017-2018

#include "BattleTanks.h"
#include "../Public/Asteroid.h"


// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	asteroidMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	asteroidMovementComponent->bAutoActivate = false;

	asteroidCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	SetRootComponent(asteroidCollisionMesh);
	asteroidCollisionMesh->SetNotifyRigidBodyCollision(true);
	asteroidCollisionMesh->SetVisibility(false);

	asteroidImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Explosion Component"));
	asteroidImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	asteroidImpactBlast->bAutoActivate = false;

	asteroidCollisionMesh->OnComponentHit.AddDynamic(this, &AAsteroid::OnHit);
	this->OnDeath.AddUniqueDynamic(this, &AAsteroid::OnAsteroidDeath);
	this->OnScore.AddUniqueDynamic(this, &AAsteroid::OnAsteroidScore);

}


// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = startingHealth;
	//this->SetActorTickEnabled(false);

	//UE_LOG(LogClass, Warning, TEXT("Setup Health: %i"), currentHealth);
	
	
	asteroidMovementComponent->ProjectileGravityScale = 0;
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogClass, Warning, TEXT("Location: %s"), *(GetRootComponent()->GetComponentLocation().ToString()));

	if(bCanDie)
		if (FPlatformTime::Seconds() >= (timeOfDeath + destroyDelay))
			this->Destroy();

	if (GetActorLocation().Y < -270.0f)
		OnScore.Broadcast();
}

float AAsteroid::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, currentHealth);

	//UE_LOG(LogClass, Warning, TEXT("Health Before Damage: %i"), currentHealth);

	currentHealth -= damageToApply;

	if (currentHealth <= 0)
		OnDeath.Broadcast();


	return damageToApply;
}

void AAsteroid::OnAsteroidDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("Death."));

	asteroidImpactBlast->Activate();
	asteroidCollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	asteroidCollisionMesh->MoveIgnoreActors.Add(this); //Ignores collision with same actor
	asteroidCollisionMesh->SetVisibility(false, true);
	bCanDie = true;

	timeOfDeath = FPlatformTime::Seconds();

	//this->SetActorTickEnabled(true);
}

void AAsteroid::OnAsteroidScore()
{
	//UE_LOG(LogTemp, Warning, TEXT("Score."));

	OnAsteroidDeath();
}

void AAsteroid::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogClass, Warning, TEXT("Hit."));

	OnAsteroidScore();
}

float AAsteroid::GetHealthPercent() const
{
	//UE_LOG(LogClass, Warning, TEXT("Health: %i"), currentHealth);
	return (float)currentHealth / (float)startingHealth;
}

void AAsteroid::LaunchAsteroid(float launchSpeed)
{
	asteroidMovementComponent->SetVelocityInLocalSpace(GetRootComponent()->GetForwardVector() * -initialVelocity * launchSpeed);
	asteroidMovementComponent->Activate();
}

void AAsteroid::LaunchAsteroidInDirection(float launchSpeed, FVector direction)
{
	asteroidMovementComponent->SetVelocityInLocalSpace(direction * initialVelocity * launchSpeed);
	asteroidMovementComponent->Activate();
}
