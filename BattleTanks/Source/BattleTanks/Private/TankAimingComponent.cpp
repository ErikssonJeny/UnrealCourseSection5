// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* assignedBarrel)
{
	barrel = assignedBarrel;
}


void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!barrel)
		return;

	FVector outLaunchVelocity; 
	FVector startLocation = barrel->GetSocketLocation(FName("launchLocation"));
	FVector aimDirection;

	UE_LOG(LogClass, Warning, TEXT("%s aiming at: %s."), *(GetOwner()->GetName()), *(hitLocation.ToString()));

	if (UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, launchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrel(aimDirection);

		UE_LOG(LogClass, Warning, TEXT("%s aiming at: %s."), *(GetOwner()->GetName()), *(aimDirection.ToString()));

	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("No firing solution."));
	}

	return;
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	FRotator barrelRotation = barrel->GetForwardVector().Rotation();
	FRotator aimRotation = aimDirection.Rotation();
	FRotator deltaRotation = aimRotation - barrelRotation;

	UE_LOG(LogClass, Warning, TEXT("Aiming rotation: %s."), *(aimRotation.ToString()));

	barrel->Elevate(5.5f);
}

