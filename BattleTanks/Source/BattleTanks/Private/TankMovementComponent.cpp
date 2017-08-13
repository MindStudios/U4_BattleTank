// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::SetTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::MoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->Move(Throw);
	RightTrack->Move(Throw);
}

void UTankMovementComponent::MoveBack(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->Move(-Throw);
	RightTrack->Move(-Throw);
}

void UTankMovementComponent::MoveRight(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->Move(Throw);
	RightTrack->Move(-Throw);
}

void UTankMovementComponent::MoveLeft(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->Move(-Throw);
	RightTrack->Move(Throw);
}


