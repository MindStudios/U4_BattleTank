// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = RelativeRotation.Pitch + ElevationChange;
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevationDegrees, MaxDegreesPerSecond);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}