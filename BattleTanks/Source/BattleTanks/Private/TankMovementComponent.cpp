// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Runtime/Engine/Classes/GameFramework/NavMovementComponent.h"

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

void UTankMovementComponent::MoveTracks(float LThrow, float RThrow)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->Move(-LThrow);
	RightTrack->Move(RThrow);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	MoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	MoveRight(RightThrow);
}

