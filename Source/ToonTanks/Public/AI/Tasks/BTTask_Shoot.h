﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
class ATurretPawn;
UCLASS()
class TOONTANKS_API UBTTask_Shoot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Shoot();

private:
	UPROPERTY(EditAnywhere)
	FName DistanceVariableName;
	UPROPERTY(EditAnywhere)
	FName CurrentStateVariableName_;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 100, ClampMax = 3000))
	float ShootRange_ = 500.f;
	UPROPERTY()
	ATurretPawn* TowerPawnRef_ {};

private:
	bool GetIsPlayerInRange(const UBehaviorTreeComponent& OwnerComp, float Range) const;
	bool GetCanShoot(const UBehaviorTreeComponent& OwnerComp) const;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
