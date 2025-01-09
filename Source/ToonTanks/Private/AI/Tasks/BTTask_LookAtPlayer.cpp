// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_LookAtPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyEnums/ETowerState.h"
#include "MyPawns/TurretPawn.h"


UBTTask_LookAtPlayer::UBTTask_LookAtPlayer()
{
	NodeName = TEXT("Look At Player");
	bNotifyTick = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_LookAtPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	APawn* pawnRef = OwnerComp.GetAIOwner()->GetPawn();
	if (!pawnRef)
	{
		return EBTNodeResult::Failed;
	}
	TowerPawnRef_ = Cast<ATurretPawn>(pawnRef);
	if (!TowerPawnRef_)
	{
		return EBTNodeResult::Failed;
	}
	

	return EBTNodeResult::InProgress;
}

void UBTTask_LookAtPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	TowerPawnRef_->RotateTurret(GetPlayerLocation(OwnerComp));
	
	if (!GetIsPlayerInRange(OwnerComp, PlayerOutOfRange_))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(CurrentStateVariableName_, ETowerState::Idle);
		AbortTask(OwnerComp, NodeMemory);
		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
		return;
	}

	if (GetIsPlayerInRange(OwnerComp, ShootRange_) && GetCanShoot(OwnerComp))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(CurrentStateVariableName_, ETowerState::Shooting);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

bool UBTTask_LookAtPlayer::GetIsPlayerInRange(const UBehaviorTreeComponent& OwnerComp, float Range) const
{
	float distanceToPlayer = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(DistanceVariableName_);
	return distanceToPlayer <= Range;
}

bool UBTTask_LookAtPlayer::GetCanShoot(const UBehaviorTreeComponent& OwnerComp) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(ShootVariableName_);
}

FVector UBTTask_LookAtPlayer::GetPlayerLocation(const UBehaviorTreeComponent& OwnerComp) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
}
