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
	
};
