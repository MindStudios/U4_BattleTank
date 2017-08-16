// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming states
UENUM()
enum class ECrosshairState : uint8
{
	Locked,
	Aiming,
	Reloading
};

// Forward Declaration
class UTankBarrel;
class UTankTurrent;
class AProjectile;

// Hold barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrel(UTankBarrel* BarrelToSet);
	UTankBarrel* GetBarrel() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurrent(UTankTurrent* val);
	UTankTurrent* GetTurrent() const;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 2;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	ECrosshairState CrosshairState = ECrosshairState::Reloading;


private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurrent* Turrent = nullptr;

	void MoveBarrel(FVector AimDirection);

	double LastFireTime = 0;
};