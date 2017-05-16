// Copyright Erik Jeny 2017-2018

#pragma once

#include "Components/ActorComponent.h"
#include "SpawnFactory.generated.h"

class AAsteroid;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFactoryDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API USpawnFactory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnFactory();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TArray<FVector> startLocations;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TArray<FVector> endLocations;

	UFUNCTION(BlueprintCallable, Category = "Score")
		int32 GetScoreCount() const;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AAsteroid> asteroidBP = NULL;

	UFUNCTION()
		void OnAsteroidDeath();

	UFUNCTION()
		void OnAsteroidScore();

	UPROPERTY(BlueprintAssignable, Category = "Lose")
		FFactoryDelegate OnPlayerLose;

	UFUNCTION(BlueprintCallable, Category = "Lose")
		void OnLose();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//In seconds
	UPROPERTY(EditAnywhere, Category = "Setup")
		double respawnDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float minimumSpeed = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float maximumSpeed = 3.5f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float minimumHealth = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float maximumHealth = 3.5f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 maxAsteroidCount = 30;

	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 asteroidCount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		int32 pointsCount = 0;

	UPROPERTY(EditAnywhere, Category = "Score")
		int32 scoreCount = 10;

	double lastSpawn = 0;

};
