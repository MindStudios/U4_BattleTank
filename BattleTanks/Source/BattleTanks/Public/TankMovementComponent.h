// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack; // Forward Declaration


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveBack(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveLeft(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveTracks(float LThrow, float RThrow);


private:
	// Called from the path finding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
