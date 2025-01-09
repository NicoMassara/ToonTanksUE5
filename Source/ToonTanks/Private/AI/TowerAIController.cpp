// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TowerAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MyEnums/ETowerState.h"
#include "MyGameModes/ToonTanksGameModeBase.h"

ATowerAIController::ATowerAIController()
{
}

void ATowerAIController::BeginPlay()
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
			toonTanksGameMode->OnTankDeathDelegate.AddDynamic(this, &ATowerAIController::SetPlayerDead);
		}
	}
}

void ATowerAIController::EnableShoot() const
{
	BlackboardComponent_->SetValueAsBool(CanShootVariableName, true);
}

void ATowerAIController::SetPlayerDead()
{
	if (auto toonTanksGameMode = Cast<AToonTanksGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		toonTanksGameMode->OnTankDeathDelegate.RemoveDynamic(this, &ATowerAIController::SetPlayerDead);
	}
	BlackboardComponent_->SetValueAsBool(PlayerAliveVariableName, false);
	BlackboardComponent_->SetValueAsEnum(CurrentStateVariableName, ETowerState::Idle);
}
