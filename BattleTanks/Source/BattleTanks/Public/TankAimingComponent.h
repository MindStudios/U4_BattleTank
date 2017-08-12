// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel;
class UTankTurrent;

// Hold barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void MoveBarrel(FVector AimDirection);

	void SetBarrel(UTankBarrel* BarrelToSet);

	UTankBarrel* GetBarrel() const;
	
	UTankTurrent* GetTurrent() const;

	void SetTurrent(UTankTurrent* val);

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurrent* Turrent = nullptr;
};