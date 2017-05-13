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

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);

		if (!ensure(possessedTank))
		{
			return;
		}

		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank death."));

	if (!GetPawn())
		return;

	GetPawn()->DetachFromControllerPendingDestroy();
	Destroy();
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




