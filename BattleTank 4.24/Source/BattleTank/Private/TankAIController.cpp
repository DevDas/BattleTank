// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerPawn = GetPlayerTank();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller can't find player Tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Found %s"), *(PlayerPawn->GetName()))
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetPlayerTank())
	{
		// TO DO Move ToWards The Player

		// Aim Towards The Player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire If Ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!PlayerPawn) { return nullptr; }

	return  Cast<ATank>(PlayerPawn);
}
