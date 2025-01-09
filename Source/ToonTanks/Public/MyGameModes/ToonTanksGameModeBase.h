// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"

class ATankPlayerController;
class ATankPawn;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTankDeathSignature);
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AToonTanksGameModeBase();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start Delay", meta = (AllowPrivateAccess = "true"))
	int StartDelay_ = 3;

	UPROPERTY()
	ATankPawn* TankRef_;
	UPROPERTY()
	ATankPlayerController* TankPlayerController_;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Enemy Count", meta = (AllowPrivateAccess = "true"))
	int32 TargetTurretCount_;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Camera Shake")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass_;
	UPROPERTY(EditDefaultsOnly, Category = "Combat|Camera Shake")
	TSubclassOf<UCameraShakeBase> PlayerHitCameraShakeClass_;
	UPROPERTY(EditDefaultsOnly, Category = "Combat|Camera Shake")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass_;
	UPROPERTY(EditDefaultsOnly, Category = "Combat|Camera Shake")
	TSubclassOf<UCameraShakeBase> PlayerDeathCameraShakeClass_;

private:
	void GameStartValues();
	UFUNCTION()
	void HandleGameplayStart();
	int32 SetTargetTurretCount() const;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartCountdown();
	UFUNCTION(BlueprintImplementableEvent)
	void StartGameplay();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bHasWon);
	UFUNCTION(BlueprintImplementableEvent)
	void TurretDead(int32 TurretCount);
	UFUNCTION(BlueprintImplementableEvent)
	void PlayerDamaged(float HealthRatio);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnTankDeathSignature OnTankDeathDelegate;
	void ActorDied(AActor* DeadActor);
	void ActorDamaged(AActor* DamagedActor, float HealthRatio);
};
