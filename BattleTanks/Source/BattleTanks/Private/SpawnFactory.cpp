// Copyright Erik Jeny 2017-2018

#include "BattleTanks.h"
#include "../Public/Asteroid.h"
#include "../Public/SpawnFactory.h"


// Sets default values for this component's properties
USpawnFactory::USpawnFactory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	this->OnPlayerLose.AddUniqueDynamic(this, &USpawnFactory::OnLose);

}


// Called when the game starts
void USpawnFactory::BeginPlay()
{
	Super::BeginPlay();

	lastSpawn = FPlatformTime::Seconds();
	
	
}


// Called every frame
void USpawnFactory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((lastSpawn + respawnDelay) <= FPlatformTime::Seconds())
	{
		if (asteroidCount < maxAsteroidCount)
		{
			int32 start = FMath::RandRange(0, startLocations.Num() - 1);
			int32 end = FMath::RandRange(0, endLocations.Num() - 1);
			FVector direction = (endLocations[end] - startLocations[start]).GetSafeNormal();

			UE_LOG(LogTemp, Warning, TEXT("Factory: %s, Random: %s"), *(startLocations[start].ToString()), *(endLocations[end].ToString()));

			AAsteroid* asteroid = GetWorld()->SpawnActor<AAsteroid>(asteroidBP, startLocations[start], FRotator(0, 0, 0));
			asteroid->LaunchAsteroidInDirection(FMath::RandRange(0.5f, 3.5f), direction);
			asteroid->OnDeath.AddUniqueDynamic(this, &USpawnFactory::OnAsteroidDeath);
			asteroid->OnScore.AddUniqueDynamic(this, &USpawnFactory::OnAsteroidScore);
			asteroidCount++;

			lastSpawn = FPlatformTime::Seconds();
		}
	}
}

void USpawnFactory::OnLose()
{
	GetWorld()->GetFirstPlayerController()->StartSpectatingOnly();
}

void USpawnFactory::OnAsteroidDeath()
{
	asteroidCount--;
}

void USpawnFactory::OnAsteroidScore()
{
	scoreCount--;

	if ((scoreCount == 0))
	{
		OnPlayerLose.Broadcast();
	}

}

int32 USpawnFactory::GetScoreCount() const
{
	return scoreCount;
}


