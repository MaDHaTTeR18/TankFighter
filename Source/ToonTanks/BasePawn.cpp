// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	TankBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBody"));
	TankBody->SetupAttachment(CapsuleComp);
	TankTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankTurret"));
	TankTurret->SetupAttachment(TankBody);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TankTurret);
	
}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TankTurret->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.f);
	TankTurret->SetWorldRotation(LookAtRotation);
}

void ABasePawn::Fire()
{
	if (ProjectileClass)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPoint->GetComponentLocation(),ProjectileSpawnPoint->GetComponentRotation());
		Projectile->SetOwner(this);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile not found on %s"), *GetOwner()->GetName());
		return;
	}
}
void ABasePawn::HandleDestruction()
{
	if (DestroyParticle && DeathSound && DeathCameraShakeClass)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DestroyParticle, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathCameraShakeClass);
	}
}
