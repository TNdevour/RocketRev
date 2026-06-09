// Fill out your copyright notice in the Description page of Project Settings.

#include "GateKey.h"

#include "Rocket.h"	
#include "GateKey.h"

// Sets default values
AGateKey::AGateKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SphereComp);
	
	OnActorBeginOverlap.AddDynamic(this,&AGateKey::StartKeyInteract);
	OnActorEndOverlap.AddDynamic(this,&AGateKey::CancelKeyInteract);

}

// Called when the game starts or when spawned
void AGateKey::BeginPlay()
{
	Super::BeginPlay();
	IsBeingCollected = false;
	
}

// Called every frame
void AGateKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DrawDebugSphere(GetWorld(),GetActorLocation(),30,12,FColor::Green,true, 600);

}

void AGateKey::UnlockPartnerGateDoor()
{
	if(GateDoor)
	{
		PlayCollectedFrontEndActions();//BP side
		OnGateKeyUnlocked.Broadcast(GateDoor);
		UE_LOG(LogTemp,Warning,TEXT("Timer completed and event fired off to open partner gate %s"),*GateDoor->GetName());
	
		Destroy();	
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("No GateDoor attached to GateKey: %s"), *GetName());
	}
	
}

void AGateKey::StartKeyInteract(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!IsBeingCollected && OtherActor && OtherActor->IsA(ARocket::StaticClass()))
	{
		PlayCollectingFrontEndActions();//Check for BP Implementation
		GetWorldTimerManager().SetTimer(CollectionTimerHandle,this,&AGateKey::UnlockPartnerGateDoor, GateKeyUnlockTime);
		IsBeingCollected = true;
		UE_LOG(LogTemp,Warning,TEXT("CollectionTimerStarted"));
	}
}

void AGateKey::CancelKeyInteract(AActor* OverlappedActor, AActor* OtherActor)
{
	if(IsBeingCollected && OtherActor && OtherActor->IsA(ARocket::StaticClass())){
		StopCollectingFrontEndActions();//Check for BP Implementation
		GetWorldTimerManager().ClearTimer(CollectionTimerHandle);
		IsBeingCollected = false;
		UE_LOG(LogTemp,Warning,TEXT("CollectionTimerCancelled"));
	}
	
}