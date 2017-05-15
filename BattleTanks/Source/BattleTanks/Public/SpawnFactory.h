// Copyright Erik Jeny 2017-2018

#pragma once

#include "Components/ActorComponent.h"
#include "SpawnFactory.generated.h"

class AAsteroid;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API USpawnFactory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnFactory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TArray<FVector> startLocations;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TArray<FVector> endLocations;

	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 asteroidCount = 0;

	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 scoreCount = 10;

	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 maxAsteroidCount = 30;

	//In seconds
	UPROPERTY(EditAnywhere, Category = "Setup")
		float respawnDelay = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AAsteroid> asteroidBP = NULL;

	UFUNCTION()
		void OnAsteroidDeath();

	UFUNCTION()
		void OnAsteroidScore();

	float lastSpawn = 0;
	
};
