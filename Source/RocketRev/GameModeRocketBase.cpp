// Fill out your copyright notice in the Description page of Project Settings.
#include "GameModeRocketBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceRocketBase.h"
#include "Rocket.h"



void AGameModeRocketBase::BeginPlay()
{
	Super::BeginPlay();
	
	//Get the GI
	GameInstanceRef = Cast<UGameInstanceRocketBase>(GetWorld()->GetGameInstance());

	//Get the pawn, bind its delegates
	RocketPawnRef = Cast<ARocket>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (RocketPawnRef)
	{
		RocketPawnRef->OnPlayerIsHit.AddDynamic(this,&AGameModeRocketBase::PlayerHitMgt);
	}else
	{
		UE_LOG(LogTemp, Warning,TEXT("pawn Cast failed in game mode"));
	}
	//Get all keys, bind their delegates
	TArray<AActor*> TempKeyArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AGateKey::StaticClass(), TempKeyArray);
	
	//Cast actors to populate the key array
	for (AActor* Actor : TempKeyArray)
	{
		if (AGateKey* Key = Cast<AGateKey>(Actor))
		{
			GateKeyArray.AddUnique(Key);
			UE_LOG(LogTemp, Warning,TEXT("Gate Key %s Added"), *Key->GetName());
		}
	}
	
	for(AGateKey* ThisGateKey : GateKeyArray)
	{
		if(ThisGateKey)
		{
			ThisGateKey->OnGateKeyUnlocked.AddDynamic(this, &AGameModeRocketBase::ManageGateUnlock);
		}
	}
	
	//Get all Doors
	TArray<AActor*> TempDoorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGateDoor::StaticClass(), TempDoorArray);
	//Cast actors to populate the Door array
	for (AActor* Actor : TempDoorArray)
	{
		if (AGateDoor* Door = Cast<AGateDoor>(Actor))
		{
			GateDoorArray.AddUnique(Door);
		}
	}
}

void AGameModeRocketBase::PlayerHitMgt(bool HasWon)
{
	if (HasWon)
	{
		UE_LOG(LogTemp, Warning,TEXT("GameMode Event received: Won"));
		FTimerHandle VictoryTimerHandle;
		GetWorldTimerManager().SetTimer(VictoryTimerHandle,this,&AGameModeRocketBase::ManageLevelVictory,EndLevelTimerDelay);
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode Event received: Crashed"));
		FTimerHandle LossTimerHandle;
		GetWorldTimerManager().SetTimer(LossTimerHandle, this,&AGameModeRocketBase::ManageLevelLoss,EndLevelTimerDelay);
	}
}

void AGameModeRocketBase::ManageGateUnlock(AGateDoor* UnlockedDoor)
{
	
	for(AGateDoor* ThisDoor: GateDoorArray)
	{
		if(ThisDoor && ThisDoor == UnlockedDoor)
		{
			//Unlock This Door
			ThisDoor->OpenGateDoor();
			break;
		}
	}
			
}

void AGameModeRocketBase::ManageLevelVictory()
{
	GameInstanceRef->LoadNextLevel();
}

void AGameModeRocketBase::ManageLevelLoss()
{
	GameInstanceRef->RestartLevel();
}

