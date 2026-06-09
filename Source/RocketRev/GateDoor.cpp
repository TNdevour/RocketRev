// Fill out your copyright notice in the Description page of Project Settings.
#include "GateDoor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGateDoor::AGateDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);

}

// Called when the game starts or when spawned
void AGateDoor::BeginPlay()
{
	Super::BeginPlay();
	RocketPawnRef = Cast<ARocket>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (RocketPawnRef)
	{
		//Bind something that unlocks this Gate. Needs to be implemented on the Rocket Pawn as a delegate
	}
	
}

// Called every frame
void AGateDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGateDoor::OpenGateDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Gate %s opened"), *GetName());
	PlayGateOpenEvents();//Implement this at the Blueprint end for VFX and SFX
	Destroy();
}

