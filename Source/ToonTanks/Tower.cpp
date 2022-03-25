// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle,this, &ATower::CheckFireCondition, FireRate, true);
	
}
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());;
	}
	
}


void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Tank was not found on %s"), *GetOwner()->GetName());
		return;
	}

	if (InFireRange() && Tank->bAlive)
	{
		Fire();
	}	
}

bool ATower::InFireRange()
{
	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("Tank was not found on %s"), *GetOwner()->GetName());
		return false;
	}

	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

	if (Distance <= FireRange)
	{
		return true;
	}

	return false;
}
void ATower::HandleDestruction()
{	
	Super::HandleDestruction();
	Destroy();
}
