// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerPosition.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UBTService_PlayerPosition : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerPosition();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
