// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto aimingComponent = GetAimingComponent();

	FindAimingComponent(aimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector hitLocation;

	if (GetSightRayHitLocation(hitLocation))
	{
		GetAimingComponent()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &outHitLocation) const
{
	outHitLocation = FVector(1.0);
	int32 viewportSizeX, viewportSizeY;
	FVector worldLocation, worldDirection, hitLocation;
	
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = FVector2D(viewportSizeX*crosshairX, viewportSizeY*crosshairY); //Gets absolute pixel values for crosshair
	
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, worldDirection))
	{
		GetLookVectorHitLocation(worldDirection, hitLocation);
		outHitLocation = hitLocation;
		return true;
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector direction, FVector &outHitLocation) const
{
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());
	FVector startLocation, endLocation;
	FHitResult objectHit;

	startLocation = PlayerCameraManager->GetCameraLocation();
	endLocation = startLocation + (direction * range * 100000);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetPawn());

	if (GetWorld()->LineTraceSingleByChannel(objectHit, startLocation, endLocation, ECollisionChannel::ECC_Visibility, CollisionParams))
	{
		outHitLocation = objectHit.Location;
		return true;
	}

	return false;
}

UTankAimingComponent* ATankPlayerController::GetAimingComponent()
{
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(aimingComponent))
		return NULL;

	return aimingComponent;
}

