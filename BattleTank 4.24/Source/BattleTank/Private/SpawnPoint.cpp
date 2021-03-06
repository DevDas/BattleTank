// Copyright DevDasTour


#include "SpawnPoint.h"
#include "Kismet\GameplayStatics.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (!SpawnedActor) { return; }

	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}

// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor* USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

