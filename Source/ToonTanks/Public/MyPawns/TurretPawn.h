// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterPawn.h"
#include "TurretPawn.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogTurret, Warning, All)

class ATurretAIController;

UCLASS()
class TOONTANKS_API ATurretPawn : public AShooterPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurretPawn();

private:
	TObjectPtr<ATurretAIController> TowerAIController_;
	float viewX_;
	float viewY_;

private:

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
	virtual FVector GetPawnViewLocation(float Frequency = 1.f);
};
