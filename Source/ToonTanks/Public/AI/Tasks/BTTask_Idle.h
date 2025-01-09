// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Idle.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UBTTask_Idle : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Idle();
	
private:
	UPROPERTY(EditAnywhere)
	float PlayerInRange_ = 1000.f;
	UPROPERTY(EditAnywhere)
	FName CurrentStateVariableName_;
	UPROPERTY(EditAnywhere)
	FName IsPlayerAliveVariableName_;
	
private:
	bool GetIsPlayerInRange(const UBehaviorTreeComponent& OwnerComp, float Range) const;
	bool GetIsPlayerAlive(const UBehaviorTreeComponent& OwnerComp) const;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
