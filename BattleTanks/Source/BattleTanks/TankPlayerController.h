// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
		float crosshairX = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float crosshairY = 0.33333;

	UPROPERTY(EditDefaultsOnly)
		float range = 10.0;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void SetScreenLocation(FVector2D);
	FVector2D GetScreenLocation();

	//Moves the barrel towards where teh crosshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FindAimingComponent(UTankAimingComponent* aimingComponent);

	UTankAimingComponent* GetAimingComponent();
	
};
