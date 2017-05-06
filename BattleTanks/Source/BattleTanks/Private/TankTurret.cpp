// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float degreesPerSecond)
{
	float deltaRotation = FMath::Clamp(degreesPerSecond, -1.0f, 1.0f) * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newRotation = RelativeRotation.Yaw + deltaRotation;

	SetRelativeRotation(FRotator(0.0f, newRotation, 0.0f));

	return;
}


