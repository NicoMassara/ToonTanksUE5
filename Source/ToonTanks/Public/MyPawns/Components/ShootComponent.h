// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"


class AProjectileActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName = "Shoot Component", ToolTip = "Handles Shooting"))
class TOONTANKS_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UShootComponent();
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileActor> ProjectileClass_;
	UPROPERTY(EditAnywhere, Category = "Shooter Values", meta = (ClampMin = 0.1, ClampMax = 3))
	float FireRate_ = 0.5f;

	float CurrentCooldown_;
	
private:

	bool GetCanShoot() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void HandleFire(USceneComponent* ShootPoint);
};
