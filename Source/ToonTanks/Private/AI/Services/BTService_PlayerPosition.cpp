// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_PlayerPosition.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerPosition::UBTService_PlayerPosition()
{
	NodeName = "Player Position";
}

void UBTService_PlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* playerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerRef) {return;}
	
	FVector playerLocation = playerRef->GetActorLocation();

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);
}
