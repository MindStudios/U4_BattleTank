// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurrent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurrent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, +1 is max up speed
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 20;
	
	void Rotate(float RelativeSpeed);
};
