// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogClass, Error, TEXT("TankPlayerController not possesing a tank."));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("TankPlayerController is possesing: %s."), *(controlledTank->GetName()));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
		return;

	FVector hitLocation;

	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
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

	if (GetWorld()->LineTraceSingleByChannel(objectHit, startLocation, endLocation, ECollisionChannel::ECC_Visibility))
	{
		outHitLocation = objectHit.Location;
		return true;
	}

	return false;
}

