// Fill out your copyright notice in the Description page of Project Settings.
#include "GameInstanceRocketBase.h"
#include "Kismet/GameplayStatics.h"


void UGameInstanceRocketBase::ChangeLevel(int32 NewLevel)
{
	if (CurrentLevel > 0 && CurrentLevel <= MaxLevelCount)
	{
		FString LevelName = FString::Printf(TEXT("Level_%d"), NewLevel);
		UGameplayStatics::OpenLevel(GetWorld(),*LevelName);
	}
	
}

void UGameInstanceRocketBase::RestartLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Restarting Level %d"), CurrentLevel);
	ChangeLevel(CurrentLevel);
}

void UGameInstanceRocketBase::RestartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Restarting the game from Level %d"), CurrentLevel);
	ChangeLevel(StartingLevel);
	CurrentLevel = StartingLevel;
}

void UGameInstanceRocketBase::LoadNextLevel()
{
	if (CurrentLevel < MaxLevelCount)
	{
		ChangeLevel(CurrentLevel + 1);
		CurrentLevel++;
	}else
	{
		RestartGame();
		//Replace This with a credits Level later
	}
}