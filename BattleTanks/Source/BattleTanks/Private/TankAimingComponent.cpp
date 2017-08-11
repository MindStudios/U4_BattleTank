// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;

	FVector ProjectileVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT ProjectileVelocity,
		GetBarrel()->GetSocketLocation(FName("ExitPoint")),
		//GetBarrel()->GetComponentLocation(),
		HitLocation,
		LaunchSpeed
	)) {
		FVector AimDirection = ProjectileVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s - Direction: %s, Velocity: %s"), *GetName(), *AimDirection.ToString() , *ProjectileVelocity.ToString());
		MoveBarrel(AimDirection);
	};
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("Barrel not found"));
		return;
	}

	FRotator BarrelRotator = GetBarrel()->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("Aim As Rotator: %s"), *DeltaRotator.ToString());
	GetBarrel()->Elevate(5); // TODO remove magic number
}

void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

UTankBarrel* UTankAimingComponent::GetBarrel() const
{
	return Barrel;
}