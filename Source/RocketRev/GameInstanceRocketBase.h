// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceRocketBase.generated.h"

/**
 * 
 */
UCLASS()
class ROCKETREV_API UGameInstanceRocketBase : public UGameInstance
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxLevelCount = 3;
	UPROPERTY(EditAnywhere)
	int32 StartingLevel = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentLevel =1;
	
	void ChangeLevel(int32 NewLevel);

public:
	UFUNCTION()
	void RestartLevel();
	UFUNCTION()
	void RestartGame();
	UFUNCTION()
	void LoadNextLevel();
	UFUNCTION()
	void LoadPrevLevel();
};
