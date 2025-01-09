// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_HandleShoot.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_HandleShoot::UBTService_HandleShoot()
{
	NodeName = "Handle Shoot";

}

void UBTService_HandleShoot::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	ResetTimer();
}

void UBTService_HandleShoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	bool bCanShoot = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());

	if(!bCanShoot)
	{
		if(CurrentTimer > 0)
		{
			CurrentTimer -= DeltaSeconds;
			if (CurrentTimer <= 0)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
				ResetTimer();
			}
		}
	}
}

void UBTService_HandleShoot::ResetTimer()
{
	CurrentTimer = FMath::FRandRange(FMath::Max(0.0f, ShootRate - ShootRateRandomDeviation), (ShootRate + ShootRateRandomDeviation));
	UE_LOG(LogTemp, Display, TEXT("Shoot Interval: %f"), CurrentTimer);
}

