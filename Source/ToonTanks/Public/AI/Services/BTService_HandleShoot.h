// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_HandleShoot.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UBTService_HandleShoot : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_HandleShoot();

private:
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.15f, ClampMax = 3))
	float ShootRate = 0.75f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.1f, ClampMax = 2))
	float ShootRateRandomDeviation = 0.5f;
	float CurrentTimer;
private:
	void ResetTimer();

protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

