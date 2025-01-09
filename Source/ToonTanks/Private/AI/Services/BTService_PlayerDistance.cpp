// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_PlayerDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerDistance::UBTService_PlayerDistance()
{
	NodeName = "Player Distance";
}

void UBTService_PlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* pawnRef = OwnerComp.GetAIOwner()->GetPawn();
	APawn* playerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!pawnRef || !playerRef) {return;}

	FVector pawnLocation = pawnRef->GetActorLocation();
	FVector playerLocation = playerRef->GetActorLocation();
	float distance = static_cast<float>(FVector::Dist(pawnLocation, playerLocation));

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), distance);
}
