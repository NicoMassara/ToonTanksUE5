// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawns/TankPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "MyPawns/TankPlayerController.h"


// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp_->SetupAttachment(RootComponent);
	CameraComp_ = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp_->SetupAttachment(SpringArmComp_);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController_ = GetController<ATankPlayerController>();
}

void ATankPawn::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultInputMapping_, 0);
		}
	}
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInput->BindAction(ShootAction_, ETriggerEvent::Started, this, &ATankPawn::HandleShoot);
		enhancedInput->BindAction(MoveAction_, ETriggerEvent::Triggered, this, &ATankPawn::HandleMove);
		enhancedInput->BindAction(LookAction_, ETriggerEvent::Triggered, this, &ATankPawn::HandleLook);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
	
}

void ATankPawn::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATankPawn::ShakeCamera(TSubclassOf<UCameraShakeBase> CameraShake)
{
	if (CameraShake)
	{
		TankPlayerController_->ClientStartCameraShake(CameraShake);	
	}
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController_ && MouseInputDelta_ > 0.1f)
	{
		FHitResult outHit;
		auto bHasHit = TankPlayerController_->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			outHit);

		RotateTurret(outHit.ImpactPoint);
	}

}

void ATankPawn::HandleMove(const FInputActionInstance& Instance)
{
	FVector2D moveAxisVector = Instance.GetValue().Get<FVector2D>();

	Move(moveAxisVector.Y);
	Turn(moveAxisVector.X);
}

void ATankPawn::HandleLook(const FInputActionInstance& Instance)
{
	FVector2D moveAxisVector = Instance.GetValue().Get<FVector2D>();
	MouseInputDelta_ = moveAxisVector.Length();
}

void ATankPawn::HandleShoot(const FInputActionInstance& Instance)
{
	Shoot();
}

void ATankPawn::Move(float Input)
{
	FVector deltaLocation = FVector::ZeroVector;
	float finalSpeed = Speed_ * UGameplayStatics::GetWorldDeltaSeconds(this);
	deltaLocation.X = Input * finalSpeed;
	AddActorLocalOffset(deltaLocation, true);
}

void ATankPawn::Turn(float Input)
{
	FRotator deltaRotator = FRotator::ZeroRotator;
	float finalRotationSpeed = TurnRate_ * UGameplayStatics::GetWorldDeltaSeconds(this);
	deltaRotator.Yaw = Input * finalRotationSpeed;
	AddActorLocalRotation(deltaRotator);
}


