// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingHazard.h"

AFlyingHazard::AFlyingHazard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFlyingHazard::BeginPlay()
{
	Super::BeginPlay();
	
	StartingPoint = GetActorLocation();
	DefaultStartingPoint = StartingPoint;
	DestinationPoint = StartingPoint + MovementFactor;
	float Distance = FVector::Dist(StartingPoint, DestinationPoint);
	
	MoveSpeed = Distance / TimeToMove;
	TargetLocation = DestinationPoint;
}

void AFlyingHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CurrentLocation = GetActorLocation();
	
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
	

	//Checks to Update the target location for back and forth movement
	if(NewLocation.Equals(TargetLocation, 1.0f))
	{
		if (TargetLocation.Equals(DestinationPoint, 1.0f))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Reached Destination Point, switching target to start"))
			TargetLocation = StartingPoint;
		}else if (TargetLocation.Equals(StartingPoint, 1.0f))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Reached Starting Point, switching target to Destination"))
			TargetLocation = DestinationPoint;
		}
	}
	
	SetActorLocation(NewLocation);
}
