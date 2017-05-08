// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankTrack.h"
#include "../Public/TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* setLeftTrack, UTankTrack* setRightTrack)
{
	if (!setLeftTrack || !setRightTrack)
		return;

	leftTrack = setLeftTrack;
	rightTrack = setRightTrack;
}

void UTankMovementComponent::MoveForward(float inputThrow)
{
	UE_LOG(LogTemp, Warning, TEXT("Forward throttle: %f"), inputThrow);

	leftTrack->SetThrottle(inputThrow);
	rightTrack->SetThrottle(inputThrow);
}

void UTankMovementComponent::MoveBackward(float inputThrow)
{
	UE_LOG(LogTemp, Warning, TEXT("Backward throttle: %f"), inputThrow);

	leftTrack->SetThrottle(-inputThrow);
	rightTrack->SetThrottle(-inputThrow);
}

void UTankMovementComponent::TurnLeft(float inputThrow)
{
	UE_LOG(LogTemp, Warning, TEXT("Left throttle: %f, %f"), -inputThrow, inputThrow);

	leftTrack->SetThrottle(-inputThrow);
	rightTrack->SetThrottle(inputThrow);
}

void UTankMovementComponent::TurnRight(float inputThrow)
{
	UE_LOG(LogTemp, Warning, TEXT("Right throttle: %f, %f"), inputThrow, -inputThrow);

	leftTrack->SetThrottle(inputThrow);
	rightTrack->SetThrottle(-inputThrow);
}



