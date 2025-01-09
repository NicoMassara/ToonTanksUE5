// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Idle.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MyEnums/ETowerState.h"


UBTTask_Idle::UBTTask_Idle()
{
	NodeName = "Idle";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(GetIsPlayerInRange(OwnerComp, PlayerInRange_) && GetIsPlayerAlive(OwnerComp))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(CurrentStateVariableName_, ETowerState::Focus);
		AbortTask(OwnerComp, NodeMemory);
		return EBTNodeResult::Aborted;
	}
	
	return EBTNodeResult::Succeeded;
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

