// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 *  Drives the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTrack* setLeftTrack, UTankTrack* setRightTrack);
	
	UFUNCTION(BlueprintCallable, Category = "Input")
		void MoveForward(float inputThrow);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void MoveBackward(float inputThrow);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void TurnLeft(float inputThrow);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void TurnRight(float inputThrow);


protected:

private:
	UTankTrack* leftTrack = NULL;
	UTankTrack* rightTrack = NULL;

	//Called from the pathfinding logic somewhere in the engine
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
};
