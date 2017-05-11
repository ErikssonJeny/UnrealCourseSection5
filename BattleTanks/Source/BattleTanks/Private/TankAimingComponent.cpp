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

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* setBarrel, UTankTurret* setTurret)
{
	barrel = setBarrel;
	turret = setTurret;
}

// Called to bind functionality to input
void UTankAimingComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTime;

	if (!ensure(barrel))
		return;

	if (isReloaded)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("launchLocation")), barrel->GetSocketRotation(FName("launchLocation")));
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (!ensure(barrel))
	{
		UE_LOG(LogClass, Error, TEXT("No barrel."));
		return;
	}
		

	if (!ensure(turret))
	{
		UE_LOG(LogClass, Error, TEXT("No turret."));
		return;
	}

	FVector outLaunchVelocity; 
	FVector startLocation = barrel->GetSocketLocation(FName("launchLocation"));
	FVector aimDirection;


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

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	if (!ensure (barrel || turret))
		return;

	FRotator barrelRotation = barrel->GetForwardVector().Rotation();
	FRotator aimRotation = aimDirection.Rotation();
	FRotator deltaRotation = aimRotation - barrelRotation;

	barrel->Elevate(deltaRotation.Pitch);
	turret->Rotate(deltaRotation.Yaw);
}


