// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hazard.h"
#include "FlyingHazard.generated.h"

/**
 * 
 */
UCLASS()
class ROCKETREV_API AFlyingHazard : public AHazard
{
	GENERATED_BODY()
	AFlyingHazard();
	
	public:
	UPROPERTY(EditAnywhere)
	FVector MovementFactor;
	UPROPERTY(VisibleAnywhere)
	FVector DestinationPoint;
	UPROPERTY(VisibleAnywhere)
	FVector StartingPoint;
	UPROPERTY(VisibleAnywhere)
	FVector DefaultStartingPoint;
	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation;
	UPROPERTY(EditAnywhere)
	float TimeToMove;
	UPROPERTY(VisibleAnywhere)
	bool HasReachedDestination = false;
	UPROPERTY(VisibleAnywhere)
	float MoveSpeed;
	
	bool CanMove = false;
	
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
};
