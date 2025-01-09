// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModes/ToonTanksGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "MyPawns/TankPawn.h"
#include "MyPawns/TankPlayerController.h"
#include "MyPawns/TurretPawn.h"

AToonTanksGameModeBase::AToonTanksGameModeBase()
{
	
}

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GameStartValues();
}

void AToonTanksGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == TankRef_)
	{
		TankRef_->HandleDestruction();
		if (TankPlayerController_)
		{
			TankPlayerController_->SetPlayerInputEnabled(false);
		}
		GameOver(false);
		TankRef_->ShakeCamera(PlayerDeathCameraShakeClass_);
		OnTankDeathDelegate.Broadcast();;
	}
	else if(ATurretPawn* deadTower = Cast<ATurretPawn>(DeadActor))
	{
		deadTower->HandleDestruction();
		TargetTurretCount_--;
		TurretDead(TargetTurretCount_);
		TankRef_->ShakeCamera(DeathCameraShakeClass_);
		if(TargetTurretCount_ <= 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameModeBase::ActorDamaged(AActor* DamagedActor, float HealthRatio)
{
	if (DamagedActor == TankRef_)
	{
		TankRef_->ShakeCamera(PlayerHitCameraShakeClass_);
		PlayerDamaged(HealthRatio);
	}
	else if (ATurretPawn* deadTower = Cast<ATurretPawn>(DamagedActor))
	{
		TankRef_->ShakeCamera(HitCameraShakeClass_);
	}
}

void AToonTanksGameModeBase::GameStartValues()
{
	TankRef_ = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController_ = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TargetTurretCount_ = SetTargetTurretCount();
	StartCountdown();
	
	if (TankPlayerController_)
	{
		TankPlayerController_->SetPlayerInputEnabled(false);

		/*FTimerHandle playerEnableTimerHandle;
		FTimerDelegate playerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			TankPlayerController_,
			&ATankPlayerController::SetPlayerInputEnabled,
			true);

		GetWorldTimerManager().SetTimer(
			playerEnableTimerHandle,
			playerEnableTimerDelegate,
			StartDelay_,
			false
			);*/

		FTimerHandle playerEnableTimerHandle;

		GetWorldTimerManager().SetTimer(
			playerEnableTimerHandle,
			this,
			&AToonTanksGameModeBase::HandleGameplayStart,
			StartDelay_,
			false);
	}

}

void AToonTanksGameModeBase::HandleGameplayStart()
{
	TankPlayerController_->SetPlayerInputEnabled(true);
	StartGameplay();
}


int32 AToonTanksGameModeBase::SetTargetTurretCount() const
{
	TArray<AActor*> TurretsArray;
	UGameplayStatics::GetAllActorsOfClass(this, ATurretPawn::StaticClass(), TurretsArray);
	return TurretsArray.Num();	
}