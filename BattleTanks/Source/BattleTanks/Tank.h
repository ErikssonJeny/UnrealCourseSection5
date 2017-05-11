// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UTankMovementComponent* tankMovementComponent = NULL;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	
};
