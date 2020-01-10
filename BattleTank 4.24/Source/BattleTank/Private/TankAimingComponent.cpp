// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{	
	if (!Barrel) { return; }

	FVector  OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	// calculate the outlaunch Velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed, 
		false, 
		0, 
		0, 
		ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
	
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//work-out difference between current barrel rotation, AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic

	Turret->Rotate(DeltaRotator.Yaw);
}