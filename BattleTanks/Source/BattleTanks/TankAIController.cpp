// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPlayerTank()) {
		UE_LOG(LogTemp, Warning, TEXT("AI Cant find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player: %s"), *GetPlayerTank()->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {
		// TODO Move towards the player

		// Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Move towards player
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	else {
		return Cast<ATank>(PlayerPawn);
	}
}

