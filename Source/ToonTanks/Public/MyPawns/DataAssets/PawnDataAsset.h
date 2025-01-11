// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PawnDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UPawnDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category="Movement", meta = (ClampMin = 0.1f, ClampMax = 200))
	float LookLerp_ = 20.f;

public:
	float GetLookLerp() const { return LookLerp_; }
};
