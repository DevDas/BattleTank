// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include <BattleTank\Public\TankAimingComponent.h>
#include "Tank.h"  // So We Can Implement on Death


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossedTank = Cast<ATank>(InPawn);
		if (!ensure(PossedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::OnPossedTankDeath()
{

	UE_LOG(LogTemp, Warning, TEXT("Okkkkkkkkkkkkkkkkkkkkkkk!!!!!!!!!"))
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

	// If Aiming And Locked Then Fire
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();  // TODO Don't Fire Every Frame, Limit firing rate
	}
}


