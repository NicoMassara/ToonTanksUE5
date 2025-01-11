// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Shoot.h"

#include "AIController.h"
#include "AI/TurretAIController.h"
#include "AI/DataAsset/TurretAIDataAsset.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyEnums/ETowerState.h"
#include "MyPawns/TurretPawn.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
	bNotifyTick = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!IsValid(AIData_))
	{
		AIData_ = Cast<ATurretAIController>(OwnerComp.GetAIOwner())->GetAIData();
		if (!AIData_)
		{
			UE_LOG(LogTemp, Error, TEXT("AI Data is NULL"));
			return EBTNodeResult::Failed;
		}
	}
	
	APawn* pawnRef = OwnerComp.GetAIOwner()->GetPawn();
	if (!pawnRef) { return EBTNodeResult::Failed; }
	TowerPawnRef_ = Cast<ATurretPawn>(pawnRef);
	if (!TowerPawnRef_) { return EBTNodeResult::Failed; }
	if (!GetIsPlayerInRange(OwnerComp, AIData_->GetShootRange()) || !GetCanShoot(OwnerComp))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(CurrentStateVariableName_, ETowerState::Focus);
		AbortTask(OwnerComp, NodeMemory);
		return EBTNodeResult::Aborted;
	}

	TowerPawnRef_->Shoot();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
	
	return EBTNodeResult::Succeeded;
}

bool UBTTask_Shoot::GetIsPlayerInRange(const UBehaviorTreeComponent& OwnerComp, float Range) const
{
	float distanceToPlayer = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(DistanceVariableName);
	return distanceToPlayer <= Range;
}

bool UBTTask_Shoot::GetCanShoot(const UBehaviorTreeComponent& OwnerComp) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
}
