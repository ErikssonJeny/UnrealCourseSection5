// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	aimingComponent = GetAimingComponent();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	if (ensure(playerTank))
	{
		MoveToActor(playerTank, acceptanceRadius*100);

		aimingComponent->AimAt(playerTank->GetActorLocation());

		if(aimingComponent->GetFiringStatus() == EFiringStatus::Locked)
			aimingComponent->Fire();
	}
}

UTankAimingComponent* ATankAIController::GetAimingComponent()
{
	auto aimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(aimComponent))
		return NULL;

	return aimComponent;
}




