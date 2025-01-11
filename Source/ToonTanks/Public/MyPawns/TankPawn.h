// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterPawn.h"
#include "TankPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTank, Warning, All);

class ATankPlayerController;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UTankDataAsset;
class UCameraShakeBase;

UCLASS()
class TOONTANKS_API ATankPawn : public AShooterPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping")
	UInputMappingContext* DefaultInputMapping_;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Actions")
	UInputAction* ShootAction_;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Actions")
	UInputAction* MoveAction_;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Actions")
	UInputAction* LookAction_;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComp_;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp_;
	
	TObjectPtr<UTankDataAsset> TankData_;
	
	ATankPlayerController* TankPlayerController_;

	
	float MouseInputDelta_;
	
private:
	UFUNCTION()
	void HandleMove(const FInputActionInstance& Instance);
	void HandleLook(const FInputActionInstance& Instance);
	void HandleShoot(const FInputActionInstance& Instance);

	void Move(float Input);
	void Turn(float Input);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
public:
	
	ATankPlayerController* GetTankPlayerController() const {return TankPlayerController_;}
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyControllerChanged() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDestruction() override;
	virtual void ShakeCamera(TSubclassOf<UCameraShakeBase> CameraShake);
};


