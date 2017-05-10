// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankTrack.h"
#include "../Public/TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* setLeftTrack, UTankTrack* setRightTrack)
{
	if (!ensure(setLeftTrack || setRightTrack))
		return;

	leftTrack = setLeftTrack;
	rightTrack = setRightTrack;
}

void UTankMovementComponent::MoveForward(float inputThrow)
{
	UE_LOG(LogTemp, Warning, TEXT("Forward throttle: %f"), inputThrow);

	if (!ensure(leftTrack || rightTrack))
		return;

	leftTrack->SetThrottle(inputThrow);
	rightTrack->SetThrottle(inputThrow);
}

void UTankMovementComponent::MoveBackward(float inputThrow)
{
	UE_LOG(LogTemp, Warning, TEXT("Backward throttle: %f"), inputThrow);

	if (!ensure(leftTrack || rightTrack))
		return;

	leftTrack->SetThrottle(-inputThrow);
	rightTrack->SetThrottle(-inputThrow);
}

void UTankMovementComponent::TurnLeft(float inputThrow)
{
	UE_LOG(LogTemp, Warning, TEXT("Left throttle: %f, %f"), -inputThrow, inputThrow);

	if (!ensure(leftTrack || rightTrack))
		return;

	leftTrack->SetThrottle(-inputThrow);
	rightTrack->SetThrottle(inputThrow);
}

void UTankMovementComponent::TurnRight(float inputThrow)
{
	UE_LOG(LogTemp, Warning, TEXT("Right throttle: %f, %f"), inputThrow, -inputThrow);

	if (!ensure(leftTrack || rightTrack))
		return;

	leftTrack->SetThrottle(inputThrow);
	rightTrack->SetThrottle(-inputThrow);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto moveForwardAI = MoveVelocity.GetSafeNormal();
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	MoveForward(FVector::DotProduct(moveForwardAI, tankForward));
	TurnRight(FVector::CrossProduct(moveForwardAI, tankForward).Z);

	UE_LOG(LogTemp, Warning, TEXT("%s velocity: %s"), *(GetOwner()->GetName()), *moveForwardAI.ToString());
}



