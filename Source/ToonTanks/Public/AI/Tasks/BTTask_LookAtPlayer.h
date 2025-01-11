// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_LookAtPlayer.generated.h"

class ATurretPawn;
class UTurretAIDataAsset;
/**
 * 
 */
UCLASS()
class TOONTANKS_API UBTTask_LookAtPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_LookAtPlayer();

private:
	UPROPERTY(EditAnywhere)
	FName DistanceVariableName_;
	UPROPERTY(EditAnywhere)
	FName ShootVariableName_;
	UPROPERTY(EditAnywhere)
	FName CurrentStateVariableName_;

	
	TObjectPtr<ATurretPawn> TowerPawnRef_ {};

	TObjectPtr<UTurretAIDataAsset> AIData_;

private:
	bool GetIsPlayerInRange(const UBehaviorTreeComponent& OwnerComp, float Range) const;
	bool GetCanShoot(const UBehaviorTreeComponent& OwnerComp) const;
	FVector GetPlayerLocation(const UBehaviorTreeComponent& OwnerComp) const;


protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
