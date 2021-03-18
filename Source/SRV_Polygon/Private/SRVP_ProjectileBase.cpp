// Fill out your copyright notice in the Description page of Project Settings.


#include "SRVP_ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"

// Sets default values
ASRVP_ProjectileBase::ASRVP_ProjectileBase()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASRVP_ProjectileBase::OnHit);

	// Players can't walk on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 20000.0f;
	ProjectileMovement->MaxSpeed = 20000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	ImpulseForceMultiply = 1.0f;
	DecalSize = 24.0f;

	InitialLifeSpan = 3.0f;
}

void ASRVP_ProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	MakeDecal(Hit);
	
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * ImpulseForceMultiply, GetActorLocation());
		Destroy();
	}
}

void ASRVP_ProjectileBase::MakeDecal(FHitResult Hit)
{
	if (!IsMakeFirstStrike)
	{
		if (Hit.bBlockingHit)
		{
			FActorSpawnParameters p;
			p.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			const FQuat rotToSurface = FRotationMatrix::MakeFromZ(Hit.Normal).ToQuat();
			const FQuat rotAroundZ = FQuat(Hit.Normal, 6.28f * FMath::FRand());

			ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(Hit.ImpactPoint, FRotator(rotAroundZ * rotToSurface), p);

			if (decal)
			{
				float scale = 0.8f + 0.4f * FMath::FRand();

				const auto material = UMaterialInstanceDynamic::Create(BulletHole, this);
				decal->SetDecalMaterial(material);
				decal->SetActorScale3D(FVector(1.0f, scale, scale));
				decal->GetDecal()->DecalSize = FVector(0.1f, DecalSize, DecalSize);

			}
			
		}
	}

	IsMakeFirstStrike = true;
}

