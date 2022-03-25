// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

//Setting Default Values
ATank::ATank()
{
	TankCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	TankCameraArm->SetupAttachment(RootComponent);
	TankCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
	TankCamera->SetupAttachment(TankCameraArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::RotateCanon);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed ,this, &ATank::Fire);

}
void ATank::Move(float Value)
{
	FVector DeltaLocation(0.0f);
	DeltaLocation.X += (Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this));
	AddActorLocalOffset(DeltaLocation,true);
}
void ATank::Turn(float Value)
{
	FRotator DeltaRotation(0.0f);
	DeltaRotation.Yaw+= (Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this));
	AddActorLocalRotation(DeltaRotation,true);
}

void ATank::RotateCanon(float Value)
{
	
	if (!TankPlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller not found on %s"), *GetOwner()->GetName());
		return;
	}
	
	FHitResult HitResult;
	TankPlayerController->GetHitResultUnderCursor
	(
		ECollisionChannel::ECC_Visibility,
		false,
		HitResult
	);
	RotateTurret(HitResult.ImpactPoint);
	
}


void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
	bAlive = false;
}

