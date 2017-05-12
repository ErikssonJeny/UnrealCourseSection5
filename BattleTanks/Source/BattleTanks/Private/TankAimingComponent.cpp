// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/Projectile.h"
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

	lastFireTime = FPlatformTime::Seconds();
	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ammoCount <= 0)
	{
		firingStatus = EFiringStatus::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTime)
	{
		firingStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		firingStatus = EFiringStatus::Aiming;
	}
	else
	{
		firingStatus = EFiringStatus::Locked;
	}

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* setBarrel, UTankTurret* setTurret)
{
	barrel = setBarrel;
	turret = setTurret;
}

void UTankAimingComponent::Fire()
{

	if (!ensure(barrel))
		return;

	if (firingStatus == EFiringStatus::NoAmmo)
		return;

	if (firingStatus != EFiringStatus::Reloading)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("launchLocation")), barrel->GetSocketRotation(FName("launchLocation")));
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
		ammoCount--;
	}
}

int32 UTankAimingComponent::GetAmmoCount() const
{
	return ammoCount;
}

void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (!ensure(barrel))
	{
		return;
	}
		

	if (!ensure(turret))
	{
		return;
	}

	FVector outLaunchVelocity; 
	FVector startLocation = barrel->GetSocketLocation(FName("launchLocation"));


	if (UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, launchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrel(aimDirection);
	}
	else
	{
	}

	return;
}

void UTankAimingComponent::MoveBarrel(FVector newAimDirection)
{
	if (!ensure (barrel || turret))
		return;

	FRotator barrelRotation = barrel->GetForwardVector().Rotation();
	FRotator aimRotation = newAimDirection.Rotation();
	FRotator deltaRotation = aimRotation - barrelRotation;

	barrel->Elevate(deltaRotation.Pitch);
	
	if (deltaRotation.Yaw < 180)
		turret->Rotate(deltaRotation.Yaw);
	else
		turret->Rotate(-deltaRotation.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(barrel))
		return false;

	return !barrel->GetForwardVector().Equals(aimDirection, 0.01f);
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return firingStatus;
}


