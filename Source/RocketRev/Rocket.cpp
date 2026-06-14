// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"

#include "Hazard.h"
#include "LandingPlatform.h"

// Sets default values
ARocket::ARocket()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	
	OnActorBeginOverlap.AddDynamic(this, &ARocket::RocketCollision);
	//make the mesh movable
	StaticMesh->SetMobility(EComponentMobility::Movable);
	//allow physics
	StaticMesh->SetSimulatePhysics(true);
	//Set collision mode
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Provide collision profile
	StaticMesh->SetCollisionProfileName("Pawn");
	//linear and angular damping
	StaticMesh->SetLinearDamping(1);
	StaticMesh->SetAngularDamping(3);

}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	IsPlaying = true;
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARocket::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARocket::RocketCollision(AActor* OverlappedActor, AActor* OtherActor)
{
	
	if (OtherActor->IsA(ALandingPlatform::StaticClass()) && IsPlaying)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rocket won! It got to the %s"), *OtherActor->GetName());
		DeactivatePlayVariables();
		PlayVictoryFrontEndEvents();
		OnPlayerIsHit.Broadcast(true);
	}else if (OtherActor->IsA(AHazard::StaticClass()) && IsPlaying)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rocket crashed into %s"), *OtherActor->GetName());
		DeactivatePlayVariables();
		PlayCrashFrontEndEvents();
		OnPlayerIsHit.Broadcast(false);
	}
}

void ARocket::DeactivatePlayVariables()
{
	IsPlaying = false;
	IsUsingLeftThruster = false;
	IsUsingRightThruster = false;
	IsUsingMainThruster = false;
}
