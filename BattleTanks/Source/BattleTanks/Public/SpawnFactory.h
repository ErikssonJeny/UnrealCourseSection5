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

	UFUNCTION(BlueprintCallable, Category = "Score")
		int32 GetPointsCount() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
		int32 GetLevelNumber() const;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AAsteroid> asteroidBP = NULL;

	UFUNCTION()
		void OnAsteroidDeath();

	UFUNCTION()
		void OnAsteroidScore();

	UPROPERTY(BlueprintAssignable, Category = "Lose")
		FFactoryDelegate OnPlayerLose;

	UPROPERTY(BlueprintAssignable, Category = "Achievement")
		FFactoryDelegate OnPlayerAchievement;

	UFUNCTION(BlueprintCallable, Category = "Lose")
		void OnLose();

	UFUNCTION(BlueprintCallable, Category = "Lose")
		void OnAchievement();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//In seconds
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		double respawnDelay = 3.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float minimumSpeed = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float maximumSpeed = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float minimumHealth = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float maximumHealth = 3.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 maxAsteroidCount = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 asteroidCount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 asteroidDeaths = 0;

	UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 pointsCount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 levelNumber = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Score")
		int32 scoreCount = 10;

	void SetTickTrue();

	double lastSpawn = 0;

	int32 globalAsteroidDeaths = 0;

	bool bHasLost = false;

	void AdvanceLevel();

};
