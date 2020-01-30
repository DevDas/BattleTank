// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BattleTank.h"
#include "Engine/World.h"
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
		float TrackmaxDrivingForce = 40000000;

private:
	UTankTrack();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
