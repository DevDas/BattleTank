// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) // On Tank_BP You Can Add This Mesh Component Custom Section
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Set A Throttle Between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	// Max Force Per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackmaxDrivingForce = 40000000; // Assume 40 Ton Tank, And 1g Accelleration
};
