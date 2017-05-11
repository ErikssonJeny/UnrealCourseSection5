// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	if (ensure(playerTank))
	{
		MoveToActor(playerTank, acceptanceRadius);

		GetAimingComponent()->AimAt(playerTank->GetActorLocation());
		GetAimingComponent()->Fire();
	}
}

UTankAimingComponent* ATankAIController::GetAimingComponent()
{
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(aimingComponent))
		return NULL;

	return aimingComponent;
}




