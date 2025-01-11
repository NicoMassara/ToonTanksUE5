// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ShooterDataAsset.generated.h"

/**
 * 
 */
class AProjectileActor;
UCLASS()
class TOONTANKS_API UShooterDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileActor> ProjectileClass_;
	UPROPERTY(EditAnywhere, Category = "Shooter Values", meta = (ClampMin = 0.1, ClampMax = 3))
	float FireRate_ = 0.5f;

public:
	TSubclassOf<AProjectileActor> GetProjectile() const {return ProjectileClass_;}
	float GetFireRate() const {return FireRate_;}
};