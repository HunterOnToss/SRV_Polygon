// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/SRVP_HealthComponent.h"

// Sets default values for this component's properties
USRVP_HealthComponent::USRVP_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100;
	Health = DefaultHealth;
	
}


// Called when the game starts
void USRVP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &USRVP_HealthComponent::TakeDamage);
	}
	
}

// Called every frame
void USRVP_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USRVP_HealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	FString const Msg = FString::SanitizeFloat(Health);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Msg);
	
}


