// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include <BattleTank\Public\TankAimingComponent.h>


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move Towards The Player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check Radius is in Cm

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	// Aim Towards The Player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire If Ready
	AimingComponent->Fire();  // TODO Don't Fire Every Frame, Limit firing rate
	
}
