// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UTankAimingComponent* ATank::GetAimComponent() const
{
	return TankAimingComponent;
}

void ATank::AimAt(FVector HitLocation)
{
	GetAimComponent()->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire()
{
	UE_LOG(LogTemp, Error, TEXT("Fire!"));

	GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		GetAimComponent()->GetBarrel()->GetSocketLocation(FName("ExitPoint")),
		GetAimComponent()->GetBarrel()->GetSocketRotation(FName("ExitPoint"))
	);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	GetAimComponent()->SetBarrel(BarrelToSet);
}

void ATank::SetTurrentReference(UTankTurrent* TurrentToSet)
{
	GetAimComponent()->SetTurrent(TurrentToSet);
}

