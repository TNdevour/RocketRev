// Fill out your copyright notice in the Description page of Project Settings.
#include "RocketController.h"
#include "InputMappingContext.h"
#include "Rocket.h"



ARocketController::ARocketController()
{
	
}

void ARocketController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Rocket Controller BeginPlay"));
	
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{			
			Subsystem->AddMappingContext(IMC_Rocket, 0);
			UE_LOG(LogTemp, Warning, TEXT("IMC_Rocket Live"));
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("IMC mapping failed"));
		}
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Get local Player"));
	}
	
	
	
	
}

void ARocketController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RocketPawnRef = Cast<ARocket>(InPawn);
	if (RocketPawnRef)
	{
		RocketPawnRef->OnPlayerIsHit.AddDynamic(this, &ARocketController::RocketHitResponse);
		UE_LOG(LogTemp, Warning, TEXT("Pawn Delegate assigned"));
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("New Cast Failed"));
	}
}

void ARocketController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EIC =	Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(BoostAction,ETriggerEvent::Triggered,this, &ARocketController::BoostInput);
		EIC->BindAction(TurnAction,ETriggerEvent::Triggered,this, &ARocketController::TurnInput);
		UE_LOG(LogTemp, Warning, TEXT("EIC Inputs bound"));
	}
}

void ARocketController::BoostInput(const FInputActionValue& Input)
{
	bool bValue = Input.Get<bool>();
	if (RocketPawnRef)
	{
		
		float ForceFactor = RocketPawnRef->ForceFactor;
		
		RocketPawnRef->StaticMesh->AddForce(RocketPawnRef->GetActorUpVector()*ForceFactor, NAME_None, true);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Input Value: %s"), *Input.ToString());
}

void ARocketController::TurnInput(const FInputActionValue& Input)
{
	float InputValue = Input.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("Input Value: %f"), InputValue);
	
	float TurnFactor = InputValue * RocketPawnRef->TurnFactor * GetWorld()->GetDeltaSeconds();
	FVector TorqueVector = FVector(0.0f, TurnFactor, 0.0f);
	
	RocketPawnRef->StaticMesh->AddTorqueInRadians(TorqueVector, NAME_None, true);
}

void ARocketController::SetPlayerEnabled(bool bEnable)
{
	if (bEnable)
	{
		EnableInput(this);
	}else
	{
		DisableInput(this);
	}
}

void ARocketController::RocketHitResponse(bool HasWon)
{
	if (HasWon)
	{
		SetActorTickEnabled(false);
		SetPlayerEnabled(false);
	}else
	{
		SetActorTickEnabled(false);
		SetPlayerEnabled(false);
	}
}