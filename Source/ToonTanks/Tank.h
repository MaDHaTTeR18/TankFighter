// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Camera Components")
	class UCameraComponent* TankCamera;
	UPROPERTY(VisibleAnywhere, Category = "Camera Components")
	class USpringArmComponent* TankCameraArm;

	UPROPERTY(EditAnywhere, Category="Movement")
	float Speed = 300.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.0f;

	void Move(float Value);
	void Turn(float Value);
	void RotateCanon(float Value);


	APlayerController* TankPlayerController;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};