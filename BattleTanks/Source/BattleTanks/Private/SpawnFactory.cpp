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
	this->OnPlayerAchievement.AddUniqueDynamic(this, &USpawnFactory::OnAchievement);

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
			asteroid->LaunchAsteroidInDirection(FMath::RandRange(minimumSpeed, maximumSpeed), direction);
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
	globalAsteroidDeaths++;
	asteroidDeaths++;
	pointsCount++;

	if (globalAsteroidDeaths == 100)
		OnPlayerAchievement.Broadcast();

	if (asteroidDeaths == maxAsteroidCount)
		AdvanceLevel();
}

void USpawnFactory::OnAsteroidScore()
{
	if(!bHasLost)
		scoreCount--;

	if ((scoreCount == 0))
	{
		OnPlayerLose.Broadcast();
		bHasLost = true;
	}

}

void USpawnFactory::OnAchievement()
{
	
}

int32 USpawnFactory::GetScoreCount() const
{
	return scoreCount;
}

int32 USpawnFactory::GetPointsCount() const
{
	return pointsCount;
}

int32 USpawnFactory::GetLevelNumber() const
{
	return levelNumber;
}

//Resets level and hardens difficulty
void USpawnFactory::AdvanceLevel()
{
	this->SetComponentTickEnabled(false); //Pause spawning immediately

	FTimerHandle waste;	

	levelNumber++;
	maxAsteroidCount = (int32)(maxAsteroidCount*1.25f);
	respawnDelay = (double)FMath::Clamp((float)(respawnDelay - 0.1f), 0.5f, 100.0f); //Respawn Delay doesn't work very well if it isn't a double
	minimumSpeed = minimumSpeed * 1.1f;
	maximumSpeed = maximumSpeed * 1.1f;
	pointsCount = pointsCount + scoreCount*10;
	scoreCount++;
	asteroidDeaths = 0;
	asteroidCount = 0;
	
	GetWorld()->GetTimerManager().SetTimer(waste, this, &USpawnFactory::SetTickTrue, 10.0f); //Resume after 10 seconds
}

void USpawnFactory::SetTickTrue()
{
	return this->SetComponentTickEnabled(true);
}


