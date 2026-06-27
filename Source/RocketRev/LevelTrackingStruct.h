// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils/UserDefinedStruct.h"
#include "LevelTrackingStruct.generated.h"

/**
 * 
 */
UCLASS()
class ROCKETREV_API ULevelTrackingStruct : public UUserDefinedStruct
{
	GENERATED_BODY()
	
public:
	ULevelTrackingStruct();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelTrackingStruct")
	FString LevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelTrackingStruct")
	bool bHasBeenCleared = false;
	
};
