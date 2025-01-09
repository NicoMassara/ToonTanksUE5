// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActors/ProjectileActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectileActor::AProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent_ = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent_;
	
	SphereComponent_ = CreateDefaultSubobject<USphereComponent>("Sphere Collider");
	SphereComponent_->SetupAttachment(MeshComponent_);

	ParticleComponent_ = CreateDefaultSubobject<UParticleSystemComponent>("Particle System");
	ParticleComponent_->SetupAttachment(RootComponent);
	
	ProjectileMovementComponent_ = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
}

void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent_->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);

	if (ShootSound_)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			ShootSound_,
			GetActorLocation()
			);
	}
}

void AProjectileActor::OnHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* myOwner = GetOwner();
	if (!myOwner) return;

	AController* myOwnerInstigator = myOwner->GetInstigatorController();
	UClass* damageTypeClass = UDamageType::StaticClass();

	if (Other && Other != this && Other != myOwner)
	{
		HandleDamage(Other, myOwnerInstigator, damageTypeClass);
	}

	HandleHit();
	
	MeshComponent_->OnComponentHit.RemoveDynamic(this, &AProjectileActor::OnHit);
}

void AProjectileActor::HandleDamage(AActor* Other, AController* OwnerInstigator, UClass* DamageType)
{
	UGameplayStatics::ApplyDamage(Other,Damage_,OwnerInstigator,this, DamageType);
}

void AProjectileActor::HandleHit()
{
	if (HitParticles_)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
		this,
		HitParticles_,
		GetActorLocation(),
		FRotator::ZeroRotator,
		FVector{HitParticlesScale_},
		true
		);
	}
	if (HitSound_)
	{
		UGameplayStatics::SpawnSoundAtLocation(
		this,
		HitSound_,
		GetActorLocation()
		);
	}

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	FTimerHandle destroyTimerHandler;
	GetWorldTimerManager().SetTimer(
		destroyTimerHandler,
		this,
		&AProjectileActor::HandleDestroy,
		0.5f,
		false);
}

void AProjectileActor::HandleDestroy()
{
	Destroy();
}

// Called when the game starts or when spawned
