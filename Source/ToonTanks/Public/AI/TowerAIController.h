// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TowerAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATowerAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATowerAIController();

private:
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	UBehaviorTree* BehaviorTree_;
	UPROPERTY(EditAnywhere, Category = "Behavior Tree|Variables Names")
	FName CurrentStateVariableName;
	UPROPERTY(EditAnywhere, Category = "Behavior Tree|Variables Names")
	FName CanShootVariableName;
	UPROPERTY(EditAnywhere, Category = "Behavior Tree|Variables Names")
	FName PlayerAliveVariableName;

	UBlackboardComponent* BlackboardComponent_;

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	void EnableShoot() const;
	UFUNCTION()
	void SetPlayerDead();
};
