// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SRVP_ShootComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USRVP_ShootComponent::USRVP_ShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RangeOfTraceFire = 10000.0f;

	bIsTraceFire = false;
	bIsProjectileFire = false;

}


// Called when the game starts
void USRVP_ShootComponent::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void USRVP_ShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USRVP_ShootComponent::OnShoot()
{
	if (bIsTraceFire)
	{
		LineTraceShoot();
	}

	if (bIsProjectileFire)
	{
		ProjectileShoot();
	}
}

void USRVP_ShootComponent::LineTraceShoot()
{
	FHitResult Hit;

	FVector const Start = Location;
	FVector const End = Start + (Rotation * RangeOfTraceFire);
	
	Hit = TraceForward(Start, End);
	
}

void USRVP_ShootComponent::ProjectileShoot()
{
	
}

FHitResult USRVP_ShootComponent::TraceForward_Implementation(FVector StartLocation, FVector EndLocation)
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 2.0f);
	
	if (bHit)
	{
		DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5,5,5), FColor::Emerald, false, 2.0f);
	}

	return Hit;
}

