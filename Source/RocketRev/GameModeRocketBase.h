// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GateKey.h"
#include "GateDoor.h"
#include "GameInstanceRocketBase.h"

#include "GameModeRocketBase.generated.h"

/**
 * 
 */
UCLASS()
class ROCKETREV_API AGameModeRocketBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ARocket* RocketPawnRef;
	UGameInstanceRocketBase* GameInstanceRef;
	
	UPROPERTY(EditAnywhere)
	float EndLevelTimerDelay = 2.0f;
	
	UFUNCTION()
	void PlayerHitMgt(bool HasWon);
	
	UFUNCTION(BlueprintCallable)
	void ManageLevelVictory();
	
	UFUNCTION(BlueprintCallable)
	void ManageLevelLoss();

	UFUNCTION()
	void ManageGateUnlock(AGateDoor* UnlockedDoor);

	TArray<AGateKey*> GateKeyArray;
	TArray<AGateDoor*> GateDoorArray;
	
protected:
	virtual  void BeginPlay();
	
};
