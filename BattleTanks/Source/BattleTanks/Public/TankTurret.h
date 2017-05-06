// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision", "Lighting"))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//Relative speed between -1 and 1
	void Rotate(float);

private:

	UPROPERTY(EditAnywhere)
		float maxDegreesPerSecond = 35.0f;
	
};
