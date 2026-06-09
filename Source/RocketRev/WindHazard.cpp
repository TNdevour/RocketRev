// Fill out your copyright notice in the Description page of Project Settings.
#include "WindHazard.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWindHazard::AWindHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(StaticMesh);
	
	OnActorBeginOverlap.AddDynamic(this, &AWindHazard::OnTrapOverlap);
	OnActorEndOverlap.AddDynamic(this, &AWindHazard::OnTrapEndOverlap);

}

// Called when the game starts or when spawned
void AWindHazard::BeginPlay()
{
	Super::BeginPlay();
	RocketPawnRef = Cast<ARocket>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (RocketPawnRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rocket Pawn Ref online for WindHazard %s "), *GetName());
	}
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWindHazard::ToggleTrap, TrapToggleInterval, true);
	
}

// Called every frame
void AWindHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RocketPawnRef && PlayerInTrap && IsTrapActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rocket Pawn in active trap. Attempting to push"));
		RocketPawnRef->StaticMesh->AddForce(GetActorForwardVector()* TrapPushStrength, NAME_None, false);
		
	}

}

void AWindHazard::OnTrapOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor->IsA(ARocket::StaticClass()))
	{			
		PlayerInTrap = true;
		UE_LOG(LogTemp, Warning, TEXT("Player in trap"));
	}	
}

void AWindHazard::OnTrapEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor->IsA(ARocket::StaticClass()))
	{
		PlayerInTrap = false;
		UE_LOG(LogTemp, Warning, TEXT("Player out of trap"));
	}
}

void AWindHazard::ToggleTrap()
{
	if (IsTrapActive)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Trap Active"));
		IsTrapActive = false;
		
		
		StopFrontEndTrapActivatedEvents();
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("Trap Inactive"));
		IsTrapActive = true;
		PlayFrontEndTrapActivatedEvents();
	}
}

