// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Drive The Tracks
	DriveTrack();
	// Apply Sideways Force
	ApplySidewaysForce();
	// To Stop The Tank
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate The Slippage Speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out Therequired acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetTimeSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector()); // accelaration unit is m/s2

	// Calculate and apply Sideways (F = ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Because There Are Two Tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// If We Press Multiple Button Then The Throttle is Greater Than 1 , To Fix This
	CurrentThrottle = FMath::Clamp<float>((CurrentThrottle + Throttle), -1, +1); 
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackmaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}