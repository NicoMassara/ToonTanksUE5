// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Idle.generated.h"

class ATurretPawn;
class UTurretAIDataAsset;
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
	FName CurrentStateVariableName_;
	UPROPERTY(EditAnywhere)
	FName IsPlayerAliveVariableName_;

	TObjectPtr<UTurretAIDataAsset> AIData_;
	TObjectPtr<ATurretPawn> TurretRef_;
	
private:
	bool GetIsPlayerInRange(const UBehaviorTreeComponent& OwnerComp, float Range) const;
	bool GetIsPlayerAlive(const UBehaviorTreeComponent& OwnerComp) const;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
