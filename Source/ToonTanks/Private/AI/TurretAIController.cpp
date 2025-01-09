// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TurretAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MyEnums/ETowerState.h"
#include "MyGameModes/ToonTanksGameModeBase.h"

ATurretAIController::ATurretAIController()
{
}

void ATurretAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree_)
	{
		RunBehaviorTree(BehaviorTree_);

		BlackboardComponent_ = GetBlackboardComponent();
		BlackboardComponent_->SetValueAsBool(PlayerAliveVariableName, true);
		BlackboardComponent_->SetValueAsEnum(CurrentStateVariableName, ETowerState::Idle);

		if (auto toonTanksGameMode = Cast<AToonTanksGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			toonTanksGameMode->OnTankDeathDelegate.AddDynamic(this, &ATurretAIController::SetPlayerDead);
		}
	}
}

void ATurretAIController::SetPlayerDead()
{
	if (auto toonTanksGameMode = Cast<AToonTanksGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		toonTanksGameMode->OnTankDeathDelegate.RemoveDynamic(this, &ATurretAIController::SetPlayerDead);
	}
	BlackboardComponent_->SetValueAsBool(PlayerAliveVariableName, false);
	BlackboardComponent_->SetValueAsEnum(CurrentStateVariableName, ETowerState::Idle);
}
