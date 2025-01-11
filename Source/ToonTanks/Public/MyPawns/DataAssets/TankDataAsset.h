// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnDataAsset.h"
#include "TankDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UTankDataAsset : public UPawnDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = 10f, ClampMax = 1000, Units="m/s"))
	float Speed_ = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = 1, ClampMax = 200))
	float TurnRate_ = 100.f;

public:
	float GetSpeed() const { return Speed_; }
	float GetTurnRate() const { return TurnRate_; }
};
