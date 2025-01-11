// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TurretAIController.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(TurretAILog, Warning, All)
class UTurretAIDataAsset;

UCLASS()
class TOONTANKS_API ATurretAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATurretAIController();

private:
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	UBehaviorTree* BehaviorTree_;
	UPROPERTY(EditAnywhere, Category = "Behavior Tree|Variables Names")
	FName CurrentStateVariableName;
	UPROPERTY(EditAnywhere, Category = "Behavior Tree|Variables Names")
	FName CanShootVariableName;
	UPROPERTY(EditAnywhere, Category = "Behavior Tree|Variables Names")
	FName PlayerAliveVariableName;

	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	UTurretAIDataAsset* AIData_;
	
	UBlackboardComponent* BlackboardComponent_;

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	void SetPlayerDead();
	UTurretAIDataAsset* GetAIData() const;
};
