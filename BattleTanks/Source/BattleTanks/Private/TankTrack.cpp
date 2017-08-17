// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysCounterForce();
	DriveTrack();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysCounterForce()
{
	// work out the required acceleration this frame to correct
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways counter force (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::Move(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * MaxSpeed * CurrentThrottle;
	auto ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}