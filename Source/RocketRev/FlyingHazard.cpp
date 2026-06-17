// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingHazard.h"

#include "RocketRev.h"

AFlyingHazard::AFlyingHazard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFlyingHazard::BeginPlay()
{
	Super::BeginPlay();
	
	StartingPoint = GetActorLocation();
	DestinationPoint = StartingPoint + MovementFactor;
	float Distance = FVector::Dist(StartingPoint, DestinationPoint);
	
	
	
	for (int i = 0; i < MovementFactorArray.Num(); i++)
	{
		if (i == 0)
		{
			TargetLocationArray.AddUnique(StartingPoint + MovementFactorArray[i]);
			Distance = FMath::Abs( FVector::Dist(StartingPoint, TargetLocationArray[0]));
		}else
		{
			TargetLocationArray.AddUnique(TargetLocationArray[i -1 ]  + MovementFactorArray[i]);
		}
	}
	
	MoveSpeed = FMath::Abs(Distance / TimeToMove);
	
	if (TargetLocationArray.Num() > 0)
	{
		DestinationPoint = TargetLocationArray[0];
	}else
	{
		DestinationPoint = StartingPoint;
	}
	
	
	TargetLocation = DestinationPoint;
}

void AFlyingHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CurrentLocation = GetActorLocation();
	
	
	

	//Checks to Update the target location for back and forth movement
	/*if(NewLocation.Equals(TargetLocation, 1.0f))
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
	}*/
	
	if (TargetLocationArray.Num() == 0)
	{
		UE_LOG(MyLog, Warning, TEXT("No target location found!"));
	}else if (TargetLocationArray.Num() == 1)
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
		//UE_LOG(MyLog, Warning, TEXT("Theres a single Target Location"));
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
	}else if(TargetLocationArray.Num() > 1){//when using multiple target locations, the idea is to iterate through them all
		//UE_LOG(MyLog, Warning, TEXT("Theres multiple Target Locations"));
		
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
		
		if (NewLocation.Equals(TargetLocation, 1.0f))
		{
			for (int i = 0; i < TargetLocationArray.Num(); i++)
			{
				if (TargetLocation.Equals(TargetLocationArray[i], 1.0f))
				{
					if (i == TargetLocationArray.Num() - 1)//Checking for that final index to set it back to the starting point vector
					{
						TargetLocation = StartingPoint;
						UE_LOG(MyLog, Warning, TEXT("Final index %d Reached. Returning to Start point"), i);
						break;
					}else//all others should iterate by 1
					{
						TargetLocation = TargetLocationArray[i + 1];
						UE_LOG(MyLog, Warning, TEXT("Onwards to next vector location"));
						break;
					}
				
				}else if (TargetLocation.Equals(StartingPoint, 1.0f))//This catches the case where the final movement has made it back to the starting point in order to restart the loop
				{
					TargetLocation = TargetLocationArray[0];	
				}
			}
		}
		SetActorLocation(NewLocation);
	}
	
	
}
