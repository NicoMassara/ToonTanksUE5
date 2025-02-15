// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawns/TankPlayerController.h"
#include "GameFramework/Pawn.h"

ATankPlayerController::ATankPlayerController()
{
	
}

void ATankPlayerController::SetPlayerInputEnabled(bool bEnabled)
{
	if (bEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bEnabled;
}
