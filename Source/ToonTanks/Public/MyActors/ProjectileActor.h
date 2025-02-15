﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"
class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;
class USoundBase;
class UCameraShakeBase;
UCLASS()
class TOONTANKS_API AProjectileActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileActor();

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent_;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent_;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent_;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleComponent_;

	UPROPERTY(EditAnywhere, Category="Combat")
	float Damage_ = 10.f;

	UPROPERTY(EditAnywhere, Category="Combat|Particles")
	UParticleSystem* HitParticles_;

	UPROPERTY(EditAnywhere, Category="Combat|Particles")
	float HitParticlesScale_ = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Combat|Sounds")
	USoundBase* ShootSound_;

	UPROPERTY(EditAnywhere, Category="Combat|Sounds")
	USoundBase* HitSound_;

private:
	UFUNCTION()
	void OnHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void HandleDamage(AActor* Other, AController* OwnerInstigator, UClass* DamageType);
	void HandleHit();
	UFUNCTION()
	void HandleDestroy();

protected:
	virtual void BeginPlay() override;

public:

};
