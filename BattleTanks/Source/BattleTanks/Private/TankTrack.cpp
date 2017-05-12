// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
}

// Called every frame
void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Called in Blueprint
void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	FVector forceApplied = GetForwardVector() * currentThrottle * maxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


void UTankTrack::ApplySidewaysForce()
{
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2; //Two tracks so divide by 2
	tankRoot->AddForce(correctionForce);
}





