// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawns/ShooterPawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPawns/Components/ShootComponent.h"
#include "MyPawns/DataAssets/PawnDataAsset.h"

DEFINE_LOG_CATEGORY(LogShooterPawn)

// Sets default values
AShooterPawn::AShooterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp_ = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp_;
	
	BaseMeshComp_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMeshComp_->SetupAttachment(CapsuleComp_);
	
	TurretMeshComp_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComp_->SetupAttachment(BaseMeshComp_);
	
	ShootPoint_ = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point"));
	ShootPoint_->SetupAttachment(TurretMeshComp_);
	
	ShootComponent_ = CreateDefaultSubobject<UShootComponent>(TEXT("Shoot Component"));
}

// Called when the game starts or when spawned
void AShooterPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnDataAsset_ == nullptr)
	{
		UE_LOG(LogShooterPawn, Error, TEXT("PawnData is NULL"));
	}
	
}

void AShooterPawn::RotateTurret(FVector LookAtTarget)
{
	if (PawnDataAsset_ == nullptr)
	{
		UE_LOG(LogShooterPawn, Error, TEXT("PawnData is NULL"));
		return;
	}
	
	FRotator currentRotation = TurretMeshComp_->GetComponentRotation();
	FVector toTarget = LookAtTarget - TurretMeshComp_->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0, toTarget.Rotation().Yaw, 0);
	FRotator newRotation = FRotator(0, lookAtRotation.Yaw, 0);

	TurretMeshComp_->SetWorldRotation(FMath::RInterpTo(
		currentRotation,
		lookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		PawnDataAsset_->GetLookLerp()));
}

void AShooterPawn::Shoot()
{
	if (bIsAlive)
	{
		ShootComponent_->HandleFire(ShootPoint_);
	}
}

void AShooterPawn::HandleDestruction()
{
	bIsAlive = false;
	
	if (DeathParticle_)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
		this,
		DeathParticle_,
		GetActorLocation(),
		FRotator::ZeroRotator,
		FVector{DeathParticleScale_},
		false
		);
	}

	if (DeathSound_)
	{
		UGameplayStatics::SpawnSoundAtLocation(
		this,
		DeathSound_,
		GetActorLocation()
		);
	}
}

// Called every frame
void AShooterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

