// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallItemBase.h"
#include "RollaBall/Game/RollaBallPlayer.h"
#include "RollaBall/Game/RollaBallGameModeBase.h"

// Sets default values
ARollaBallItemBase::ARollaBallItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Mesh Object in world
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	// Set the Mesh as the root
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ARollaBallItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Call the OverlapBegin method when the Ball Item overlaps with something
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollaBallItemBase::OverlapBegin);
}

void ARollaBallItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Collect the item if overlapping with a player
	if (Cast<ARollaBallPlayer>(OtherActor) != nullptr)
	{
		Collected();
	}
}

void ARollaBallItemBase::Collected_Implementation()
{
	// retrieve game mode, and call item collection if successfully found
	ARollaBallGameModeBase* GameMode = Cast<ARollaBallGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->ItemCollected();
	}
}

