// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AController;
class AToonTanksGameModeBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, HealthRatio);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName="Health Component", ToolTip = "Handles Health and Death"))
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

private:
	UPROPERTY(EditAnywhere, Category = "Health", meta = (ClampMin = 1, ClampMax = 1000))
	float MaxHealth_ = 100.f;
	UPROPERTY(VisibleInstanceOnly, Category = "Health")
	float CurrentHealth_;
	
	UPROPERTY()
	AToonTanksGameModeBase* GameMode_;
	
private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
	void ReduceHealth(float Damage);
	void HandleDeath();

protected:
	virtual void BeginPlay() override;
	
public:
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChangedDelegate;
	float GetHealthRatio() const {return CurrentHealth_ / MaxHealth_;}
	bool GetIsAlive() const {return GetHealthRatio() > 0;}
};
