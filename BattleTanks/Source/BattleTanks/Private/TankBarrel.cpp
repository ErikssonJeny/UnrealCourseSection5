// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float degreesPerSecond)
{
	float deltaElevation = FMath::Clamp(degreesPerSecond, -1.0f, 1.0f) * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = RelativeRotation.Pitch + deltaElevation;

	SetRelativeRotation(FRotator(FMath::Clamp(newElevation, minElevation, maxElevation), 0.0f, 0.0f));

	return;
}


