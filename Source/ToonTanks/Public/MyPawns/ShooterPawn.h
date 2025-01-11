// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShooterPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogShooterPawn, Warning, All)

class UShootComponent;
class UCapsuleComponent;
class UShootComponent;
class UParticleSystem;
class USoundBase;

UCLASS(Abstract)
class TOONTANKS_API AShooterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShooterPawn();

private:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp_;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMeshComp_;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMeshComp_;

	UPROPERTY(EditAnywhere)
	USceneComponent* ShootPoint_;

	UPROPERTY(EditAnywhere)
	UShootComponent* ShootComponent_;
	
	UPROPERTY(EditAnywhere, Category = "Death")
	UParticleSystem* DeathParticle_;
	
	UPROPERTY(EditAnywhere, Category = "Death", meta = (ClampMin = .25f, ClampMax = 5f))
	float DeathParticleScale_ = 1.f;

	UPROPERTY(EditAnywhere, Category = "Death")
	USoundBase* DeathSound_;

	bool bIsAlive = true;
	
private:
protected:
	UPROPERTY(EditDefaultsOnly, Category= "Pawn Data")
	class UPawnDataAsset* PawnDataAsset_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void RotateTurret(FVector LookAtTarget);
	virtual void Shoot();
	virtual void HandleDestruction();

};


