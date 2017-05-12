// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent), hidecategories = ("Lighting"))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UTankTrack();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float throttle);

	void DriveTrack();

	//In newtons (N)
	UPROPERTY(EditDefaultsOnly)
		float maxDrivingForce = 400000; //10m/s^2

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysForce();

	float currentThrottle = 0.0f;
	
};
