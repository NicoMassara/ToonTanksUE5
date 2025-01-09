#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EWidgetState
{
	Countdown UMETA(DisplayName = "Countdown"),
	Gameplay UMETA(DisplayName = "Gameplay"),
	Endgame UMETA(DisplayName = "Endgame"),
};
