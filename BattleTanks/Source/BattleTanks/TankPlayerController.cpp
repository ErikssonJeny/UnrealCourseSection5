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
		UE_LOG(LogClass, Warning, TEXT("TankPlayerController is possesing: %s."), controlledTank->GetName());
	}

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


