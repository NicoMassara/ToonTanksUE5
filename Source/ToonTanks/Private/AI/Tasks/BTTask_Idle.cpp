// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Idle.h"

#include <ThirdParty/Imath/Deploy/Imath-3.1.9/include/Imath/ImathPlatform.h>

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyEnums/ETowerState.h"
#include "MyPawns/TurretPawn.h"


UBTTask_Idle::UBTTask_Idle()
{
	NodeName = "Idle";
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(GetIsPlayerInRange(OwnerComp, PlayerInRange_) && GetIsPlayerAlive(OwnerComp))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(CurrentStateVariableName_, ETowerState::Focus);
		AbortTask(OwnerComp, NodeMemory);
		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
	}
	return EBTNodeResult::Succeeded;
	//return EBTNodeResult::InProgress;
}

void UBTTask_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


}

bool UBTTask_Idle::GetIsPlayerInRange(const UBehaviorTreeComponent& OwnerComp, float Range) const
{
	float distanceToPlayer = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	return distanceToPlayer <= Range;
}

bool UBTTask_Idle::GetIsPlayerAlive(const UBehaviorTreeComponent& OwnerComp) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(IsPlayerAliveVariableName_);
}

FVector UBTTask_Idle::GetOrbitLocation(const FVector& Center, float Radius, float AngleDegrees, char Axis)
{
	// Convert angle from degrees to radians
	float AngleRadians = FMath::DegreesToRadians(AngleDegrees);

	float X = Center.X;
	float Y = Center.Y;
	float Z = Center.Z;

	if (Axis == 'Z' || Axis == 'z') {
		// Orbit in the X-Y plane
		X = Center.X + Radius * FMath::Cos(AngleRadians);
		Y = Center.Y + Radius * FMath::Sin(AngleRadians);
	} 
	else if (Axis == 'X' || Axis == 'x') {
		// Orbit in the Y-Z plane
		Y = Center.Y + Radius * FMath::Cos(AngleRadians);
		Z = Center.Z + Radius * FMath::Sin(AngleRadians);
	} 
	else if (Axis == 'Y' || Axis == 'y') {
		// Orbit in the X-Z plane
		X = Center.X + Radius * FMath::Cos(AngleRadians);
		Z = Center.Z + Radius * FMath::Sin(AngleRadians);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Invalid axis specified. Use 'X', 'Y', or 'Z'."));
	}

	return FVector(X, Y, Z);
}

 