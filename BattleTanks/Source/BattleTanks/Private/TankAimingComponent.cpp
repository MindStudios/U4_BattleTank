// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (GetAmmo() > 0) {
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		{
			SetCrosshairState(ECrosshairState::Reloading);
		}
		else if (IsBarrelMoving()) {
			SetCrosshairState(ECrosshairState::Aiming);
		}
		else {
			SetCrosshairState(ECrosshairState::Locked);
		}
	}
	else {
		SetCrosshairState(ECrosshairState::OutOfAmmo);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensureMsgf(Barrel, TEXT("Barrel is a null pointer"))) return false;

	if (AimDirection.Equals(GetBarrel()->GetForwardVector(), .01f)) return true;

	return false;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensureMsgf(Barrel, TEXT("Barrel is a null pointer"))) return;

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
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter must be present to prevent bug
	)) {
		AimDirection = ProjectileVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f - D: %s, V: %s"), Time, *AimDirection.ToString(), *ProjectileVelocity.ToString());
	};
}

void UTankAimingComponent::Fire()
{
	auto Barrel = GetBarrel();

	if (ensureMsgf(ProjectileBlueprint, TEXT("Projectile Blueprint not found")) 
		&& ensureMsgf(Barrel, TEXT("Barrel is a null pointer")) 
		&& GetCrosshairState() != ECrosshairState::Reloading 
		&& GetAmmo() > 0) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ExitPoint")),
			Barrel->GetSocketRotation(FName("ExitPoint"))
			);

		Projectile->Launch(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
		SetCrosshairState(ECrosshairState::Reloading);
		SetAmmo(GetAmmo() - 1);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensureMsgf(Barrel, TEXT("Barrel is a null pointer"))) return;

	FRotator BarrelRotator = GetBarrel()->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	GetBarrel()->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		GetTurrent()->Rotate(DeltaRotator.Yaw);
	}
	else {
		GetTurrent()->Rotate(-DeltaRotator.Yaw);
	}
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

ECrosshairState UTankAimingComponent::GetCrosshairState() const
{
	return CrosshairState;
}

void UTankAimingComponent::SetCrosshairState(ECrosshairState val)
{
	CrosshairState = val; 
}

int UTankAimingComponent::GetAmmo() const 
{
	return TotalAmmo; 
}

void UTankAimingComponent::SetAmmo(int val) 
{ 
	TotalAmmo = val; 
}