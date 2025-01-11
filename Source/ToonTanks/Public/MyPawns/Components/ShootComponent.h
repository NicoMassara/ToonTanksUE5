// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogShoot, Warning, All)
class AProjectileActor;
class UShooterDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName = "Shoot Component", ToolTip = "Handles Shooting"))
class TOONTANKS_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UShootComponent();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Shoot Data")
	UShooterDataAsset* ShootData_;
	float CurrentCooldown_;
	
private:
	void ResetCooldown();
	bool GetCanShoot() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void HandleFire(const USceneComponent* ShootPoint);
};
