// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "../Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	controlledTank = Cast<ATank>(GetPawn());
	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());


}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	if (ensure(playerTank))
	{
		MoveToActor(playerTank, acceptanceRadius);

		controlledTank->AimAt(playerTank->GetActorLocation());
		controlledTank->Fire();
	}
}




