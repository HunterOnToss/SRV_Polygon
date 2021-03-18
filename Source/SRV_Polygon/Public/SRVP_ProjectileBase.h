// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRVP_ProjectileBase.generated.h"

UCLASS()
class SRV_POLYGON_API ASRVP_ProjectileBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile", meta=(AllowPrivateAccess="true"));
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat", meta=(AllowPrivateAccess="true"))
	float ImpulseForceMultiply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat", meta=(AllowPrivateAccess="true"))
	float DecalSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	UMaterial* BulletHole;
	
public:	
	// Sets default values for this actor's properties
	ASRVP_ProjectileBase();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void MakeDecal(FHitResult Hit);
	
	FORCEINLINE class USphereComponent* GetCollisionComponent() const { return CollisionComponent; }

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	bool IsMakeFirstStrike = false;

};
