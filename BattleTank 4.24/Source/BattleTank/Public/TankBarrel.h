// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	// -1 is ax downward speed, and +1 is max up movement speed
	void Elevate(float RelativeSpeed);


private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 10; // Sensible Default

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevationDegrees = 40; // TODO Set

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevationDegrees = -10; // TODO Set

};
