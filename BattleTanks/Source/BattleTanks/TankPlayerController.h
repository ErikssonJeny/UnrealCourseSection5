// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		float crosshairX = 0.5;

	UPROPERTY(EditAnywhere)
		float crosshairY = 0.33333;

	UPROPERTY(EditAnywhere)
		float range = 10.0;

	ATank* GetControlledTank() const;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void SetScreenLocation(FVector2D);
	FVector2D GetScreenLocation();

	//Moves the barrel towards where teh crosshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;
	
};
