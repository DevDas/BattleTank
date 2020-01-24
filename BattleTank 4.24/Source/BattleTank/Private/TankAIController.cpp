// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank))
	{
		// TO DO Move ToWards The Player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check Radius is in Cm

		// Aim Towards The Player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire If Ready
		ControlledTank->Fire();  // TODO Don't Fire Every Frame, Limit firing rate
	}
}
