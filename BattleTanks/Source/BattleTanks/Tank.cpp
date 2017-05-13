// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
	currentHealth = startingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, currentHealth);

	currentHealth -= damageToApply;

	if (currentHealth <= 0)
		OnDeath.Broadcast();

	return damageToApply;
}

float ATank::GetHealthPercent() const
{
	UE_LOG(LogClass, Warning, TEXT("Health: %i"), currentHealth);
	return (float)currentHealth / (float)startingHealth;
}





