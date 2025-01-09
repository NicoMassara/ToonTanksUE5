// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawns/TurretPawn.h"

#include "AI/TurretAIController.h"


// Sets default values
ATurretPawn::ATurretPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();

	TowerAIController_ = GetController<ATurretAIController>();
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurretPawn::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}


