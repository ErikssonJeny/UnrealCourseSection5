// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent), hidecategories = ("Lighting"))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	
	//Relative speed between -1 and 1
	void Elevate(float);

private:

	UPROPERTY(EditAnywhere)
		float maxDegreesPerSecond = 5.5f;
	
	UPROPERTY(EditAnywhere)
		float maxElevation = 35.0f;
	
	UPROPERTY(EditAnywhere)
		float minElevation = -1.0f;
	
	
};
