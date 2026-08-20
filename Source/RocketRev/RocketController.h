// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Rocket.h"
#include "GameInstanceRocketBase.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


#include "RocketController.generated.h"

/**
 * 
 */
UCLASS()
class ROCKETREV_API ARocketController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	ARocket* RocketPawnRef;
	UGameInstanceRocketBase* GameInstanceRef;
	
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_Rocket;
	
	UPROPERTY(EditAnywhere)
	class UInputAction* BoostAction;
	
	UPROPERTY(EditAnywhere)
	class UInputAction* TurnAction;
	
	UPROPERTY(EditAnywhere)
	class UInputAction* PrevlevelDebug;
	
	UPROPERTY(EditAnywhere)
	class UInputAction* NextlevelDebug;
	
	void BoostInput(const FInputActionValue& Input);
	void TurnInput(const FInputActionValue& Input);
	
	void SetPlayerEnabled(bool bEnable);
	
	UFUNCTION()
	void RocketHitResponse(bool HasWon);
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	void BoostRelease();
	void TurnRelease();
	void PrevLevelPress();
	void NextLevelPress();
	
};
