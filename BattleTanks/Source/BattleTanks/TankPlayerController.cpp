// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Controller not possessing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank()) { return; }
	FVector OutHitLocation; // Out Parameter

	if (GetSightRayHitLocation(OutHitLocation))
		UE_LOG(LogTemp, Warning, TEXT("Hit!"));

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	
	/*FRotator OutHitRotation;
	FHitResult OutHit;
	AController* Controller = GetControlledTank()->Controller;
	Controller->GetPlayerViewPoint(OutHitLocation, OutHitRotation);

	/// Draw a line from player to the Reach value
	float Reach = 1000;
	FVector LineTraceEnd = OutHitLocation + OutHitRotation.Vector() * Reach;

	/// Line-trace (aka ray cast)
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OutHit,
		OutHitLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return OutHit.IsValidBlockingHit();*/
	OutHitLocation = FVector(0, 0, 0);
	return true;
}