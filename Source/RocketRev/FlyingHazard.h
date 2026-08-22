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
	UPROPERTY(EditAnywhere, Category="Hazard")
	FVector MovementFactor;
	UPROPERTY(EditAnywhere, Category="Hazard")
	TArray<FVector> MovementFactorArray;
	
	UPROPERTY(VisibleAnywhere, Category="Hazard")
	TArray<FVector> TargetLocationArray;
	
	UPROPERTY(VisibleAnywhere, Category="Hazard")
	FVector DestinationPoint;
	UPROPERTY(VisibleAnywhere, Category="Hazard")
	FVector StartingPoint;
	UPROPERTY(VisibleAnywhere, Category="Hazard")
	FVector TargetLocation;
	UPROPERTY(EditAnywhere, Category="Hazard")
	float TimeToMove;
	UPROPERTY(VisibleAnywhere, Category="Hazard")
	bool HasReachedDestination = false;
	UPROPERTY(VisibleAnywhere, Category="Hazard")
	float MoveSpeed;
	
	bool CanMove = false;
	const float VECTORTOLERANCE = 1.0f;
	
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
};
