// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TurretAIDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UTurretAIDataAsset : public UDataAsset
{

private:
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category= "Player Range", meta = (ClampMin = 100, ClampMax = 10000))
	float PlayerRange_ = 1000.f;
	UPROPERTY(EditAnywhere, Category= "Player Range", meta = (ClampMin = 100, ClampMax = 5000))
	float PlayerOutOfRange_ = 1000.f;
	UPROPERTY(EditAnywhere, Category= "Shooting", meta = (ClampMin = 100, ClampMax = 3000))
	float ShootRange_ = 500.f;
	UPROPERTY(EditAnywhere, Category= "Shooting", meta = (ClampMin = 0.15f, ClampMax = 3))
	float ShootRate_ = 0.75f;
	UPROPERTY(EditAnywhere, Category= "Rotation", meta = (ClampMin = 0.5f, ClampMax = 25))
	float RotationFrequency_ = 1;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "Player Range")
	float GetPlayerRange() const { return PlayerRange_; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "Player Range")
	float GetPlayerOutRange() const { return PlayerOutOfRange_; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "Shooting")
	float GetShootRange() const { return ShootRange_; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "Shooting")
	float GetShootRate() const { return ShootRate_; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "Rotation")
	float GetRotationFreq() const { return RotationFrequency_; }
};
