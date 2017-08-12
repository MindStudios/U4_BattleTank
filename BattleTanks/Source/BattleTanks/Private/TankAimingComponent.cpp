// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;
	float Time = GetWorld()->GetTimeSeconds();

	FVector ProjectileVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT ProjectileVelocity,
		GetBarrel()->GetSocketLocation(FName("ExitPoint")),
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::TraceFullPath // Parameter must be present to prevent bug
	)) {
		FVector AimDirection = ProjectileVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f - D: %s, V: %s"), Time, *AimDirection.ToString(), *ProjectileVelocity.ToString());
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

	GetBarrel()->Elevate(DeltaRotator.Pitch);
	GetTurrent()->Rotate(DeltaRotator.Yaw);
}

UTankBarrel* UTankAimingComponent::GetBarrel() const
{
	return Barrel;
}

void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

UTankTurrent* UTankAimingComponent::GetTurrent() const
{ 
	return Turrent;
}

void UTankAimingComponent::SetTurrent(UTankTurrent* TurrentToSet)
{ 
	Turrent = TurrentToSet;
}