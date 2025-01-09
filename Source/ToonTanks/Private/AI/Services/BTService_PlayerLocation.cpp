// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_PlayerLocation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = "Player Location";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APawn* playerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerRef) {return;}
	
	FVector playerLocation = playerRef->GetActorLocation();

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);
}
