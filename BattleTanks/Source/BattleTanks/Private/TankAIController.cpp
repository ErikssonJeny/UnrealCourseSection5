// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* controlledTank = GetControlledTank();
	ATank* playerTank = GetPlayerTank();

	if (!controlledTank)
	{
		UE_LOG(LogClass, Error, TEXT("TankAIController not possesing a tank."));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("TankAIController is possesing: %s."), *(controlledTank->GetName()));
	}
	
	if (!playerTank)
	{
		UE_LOG(LogClass, Error, TEXT("Player tank not found."));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("TankAIController is aiming at: %s."), *(playerTank->GetName()));
	}

}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATank* tank = NULL;
	tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	return tank;
}



