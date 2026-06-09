// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include  "GateDoor.h"

#include "GateKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGateKeyUnlockedSignature, AGateDoor*, InGateDoor);

UCLASS()
class ROCKETREV_API AGateKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGateKey();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;
	
	UPROPERTY(BlueprintAssignable)
	FOnGateKeyUnlockedSignature OnGateKeyUnlocked;
	
	UPROPERTY(EditAnywhere)
	//Attached GateDoor to unlock. Remember to set it for each Key manually
	AGateDoor* GateDoor;
	
	UPROPERTY(EditAnywhere)
	float GateKeyUnlockTime = 2.0;
	UPROPERTY(VisibleAnywhere)
	bool IsBeingCollected = false;
	
	FTimerHandle CollectionTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void UnlockPartnerGateDoor();
	
	UFUNCTION()
	void StartKeyInteract(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void CancelKeyInteract(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCollectingFrontEndActions(); 

	UFUNCTION(BlueprintImplementableEvent)
	void StopCollectingFrontEndActions();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCollectedFrontEndActions();

};
