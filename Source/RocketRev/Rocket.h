// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/StaticMeshComponent.h"

#include "Rocket.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerIsHitSignature, bool, HasWon);

UCLASS()
class ROCKETREV_API ARocket : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARocket();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerIsHitSignature OnPlayerIsHit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void RocketCollision(AActor* OverlappedActor, AActor* OtherActor);
	
	bool IsPlaying = true;
	
	UPROPERTY(EditAnywhere, Category="Rocket")
	float ForceFactor = 200000.0f;
	
	
	UPROPERTY(EditAnywhere, Category="Rocket")
	float TurnFactor = 200.0f;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayVictoryFrontEndEvents();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCrashFrontEndEvents();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Rocket")
	bool IsUsingMainThruster = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Rocket")
	bool IsUsingLeftThruster = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Rocket")
	bool IsUsingRightThruster = false;
	
	UFUNCTION(BlueprintCallable, Category="Rocket")
	void DeactivatePlayVariables();
};
