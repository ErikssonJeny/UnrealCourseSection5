// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	FVector forceApplied = GetForwardVector() * throttle * maxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}




