// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawns/Components/ShootComponent.h"
#include "MyActors/ProjectileActor.h"


// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (CurrentCooldown_ > 0)
	{
		CurrentCooldown_ -= DeltaTime;
	}
}

void UShootComponent::HandleFire(USceneComponent* ShootPoint)
{
	if (!GetCanShoot())
	{
		return;
	}

	CurrentCooldown_ = FireRate_;
	FVector location = ShootPoint->GetComponentLocation();
	FRotator rotation = ShootPoint->GetComponentRotation();
	AProjectileActor* projectileRef =GetWorld()->SpawnActor<AProjectileActor>(
		ProjectileClass_,
		location,
		rotation
		);
	
	projectileRef->SetOwner(GetOwner());
}

bool UShootComponent::GetCanShoot() const
{
	return CurrentCooldown_ <= 0;
}

