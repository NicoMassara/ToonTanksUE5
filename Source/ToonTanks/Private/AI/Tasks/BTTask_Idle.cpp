// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Idle.h"

#include <ThirdParty/Imath/Deploy/Imath-3.1.9/include/Imath/ImathPlatform.h>

#include "AIController.h"
#include "AI/TurretAIController.h"
#include "AI/DataAsset/TurretAIDataAsset.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyEnums/ETowerState.h"
#include "MyPawns/TurretPawn.h"


UBTTask_Idle::UBTTask_Idle()
{
	NodeName = "Idle";
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	if(GetIsPlayerInRange(OwnerComp, AIData_->GetPlayerInRange() && GetIsPlayerAlive(OwnerComp)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Here 2"));
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(CurrentStateVariableName_, ETowerState::Focus);
		AbortTask(OwnerComp, NodeMemory);
		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
	}
	
	return EBTNodeResult::Succeeded;
}

void UBTTask_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
}

bool UBTTask_Idle::GetIsPlayerInRange(const UBehaviorTreeComponent& OwnerComp, float Range) const
{
	float distanceToPlayer = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	return distanceToPlayer <= Range;
}

bool UBTTask_Idle::GetIsPlayerAlive(const UBehaviorTreeComponent& OwnerComp) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(IsPlayerAliveVariableName_);
}

 