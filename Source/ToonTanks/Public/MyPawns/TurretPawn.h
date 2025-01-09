// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterPawn.h"
#include "TurretPawn.generated.h"

class ATurretAIController;

UCLASS()
class TOONTANKS_API ATurretPawn : public AShooterPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurretPawn();

private:
	UPROPERTY()
	ATurretAIController* TowerAIController_;

private:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
};
