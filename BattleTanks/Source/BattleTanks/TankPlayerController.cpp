// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h" // Intellisense Bug Fix

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Aiming Componenent not found"));
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
	auto ControlledTank = GetControlledTank();
	if (!ensureMsgf(ControlledTank, TEXT("Tank is a null pointer"))) { return; }

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(OUT HitLocation)) {
		ControlledTank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(OUT ViewPortSizeX, OUT ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D((float)ViewPortSizeX * CrossHairXLocation, (float)ViewPortSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, OUT LookDirection)) {
		return GetLookVectorHitLocation(LookDirection, OUT HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation = FVector();
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		OUT CameraWorldLocation, 
		OUT LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		OUT StartLocation,
		OUT EndLocation,
		ECollisionChannel::ECC_Visibility
	)) {
		HitLocation = HitResult.Location;
		return true;
	};

	HitLocation = FVector(0, 0, 0);
	return false;
}