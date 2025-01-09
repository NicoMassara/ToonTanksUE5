// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawns/Components/HealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "MyGameModes/ToonTanksGameModeBase.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHealth_ = MaxHealth_;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	GameMode_ = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(this));
}


void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0) return;
	if (!GetIsAlive()) return;

	ReduceHealth(Damage);

	if (!GetIsAlive())
	{
		HandleDeath();
	}
}

void UHealthComponent::ReduceHealth(float Damage)
{
	CurrentHealth_ -= Damage;
	CurrentHealth_ = FMath::Clamp(CurrentHealth_, 0, MaxHealth_);
	OnHealthChangedDelegate.Broadcast(GetHealthRatio());
	GameMode_->ActorDamaged(GetOwner(), GetHealthRatio());
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), GetHealthRatio());
}

void UHealthComponent::HandleDeath()
{
	if (GameMode_ == nullptr) { return; }
	GameMode_->ActorDied(GetOwner());
	GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::DamageTaken);
}



