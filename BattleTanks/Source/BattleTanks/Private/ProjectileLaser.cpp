// Copyright Erik Jeny 2017-2018

#include "BattleTanks.h"
#include "../Public/ProjectileLaser.h"

AProjectileLaser::AProjectileLaser()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

// Called when the game starts or when spawned
void AProjectileLaser::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AProjectileLaser::OnOverlap);
}

void AProjectileLaser::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{

}

void AProjectileLaser::LaunchProjectile(float speed)
{

}

void AProjectileLaser::OnTimerExpire()
{
	Destroy();
}


