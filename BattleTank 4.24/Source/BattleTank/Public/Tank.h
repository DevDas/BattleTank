// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

public:
	void AimAt(FVector HitLocation);

	// TODO Remove Once Firing Is Moved To Aiming Component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000; // Sensible Starting Value of 1000 m/s

	UFUNCTION(BlueprintCallable, Category = "Firing") // Call From Tank_BP
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UClass* ProjectileBlueprint;  // can be set any class from tank_bp (self) because here is UClass*

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UTankBarrel* Barrel = nullptr; // TODO Remove

	double LastFireTime = 0;
};