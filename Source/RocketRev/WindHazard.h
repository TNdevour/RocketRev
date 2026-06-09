// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Rocket.h"

#include "WindHazard.generated.h"

UCLASS()
class ROCKETREV_API AWindHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWindHazard();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere)
	bool IsTrapActive;
	
	ARocket* RocketPawnRef;
	UPROPERTY(EditAnywhere, Category="Trap")
	float TrapPushStrength = 100.0f;
	UPROPERTY(EditAnywhere, Category="Trap", BlueprintReadOnly)
	float TrapToggleInterval = 5.0f;
	UPROPERTY(VisibleAnywhere, Category="Trap", BlueprintReadOnly)
	bool PlayerInTrap = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnTrapOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnTrapEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayFrontEndTrapActivatedEvents();
	
	UFUNCTION(BlueprintImplementableEvent)
	void StopFrontEndTrapActivatedEvents();
	
	void ToggleTrap();

};
