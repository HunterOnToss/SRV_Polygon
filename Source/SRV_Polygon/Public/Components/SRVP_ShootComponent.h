// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRVP_ShootComponent.generated.h"

class ASRVP_ProjectileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SRV_POLYGON_API USRVP_ShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USRVP_ShootComponent();

	UFUNCTION(BlueprintCallable)
	void OnShoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LineTrace")
	float RangeOfTraceFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LineTrace")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LineTrace")
	FVector Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shoot")
	bool bIsTraceFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shoot")
	bool bIsProjectileFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	float BulletSpread;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class ASRVP_ProjectileBase> ProjectileClass;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void LineTraceShoot();
	void ProjectileShoot();

	UFUNCTION(BlueprintNativeEvent)
	FHitResult TraceForward(FVector StartLocation, FVector EndLocation);
	FHitResult TraceForward_Implementation(FVector StartLocation, FVector EndLocation);
	
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FTransform GetProjectileTransform() const;

	FVector GetProjectileTranslation(FRotator ProjectileRotation) const;

	FRotator GetProjectileRotation() const;
	
};
