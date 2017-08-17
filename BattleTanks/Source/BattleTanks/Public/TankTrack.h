// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	// -1 is max backward speed, +1 is max forward speed
	void Move(float Throttle);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxSpeed = 10000;
	
private:
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysCounterForce();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle;
	void DriveTrack();
};
