// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowfallItem.h"

// Sets default values
ASnowfallItem::ASnowfallItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	W_ModelStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemModel"));
	if(W_ModelStaticMeshComponent->SetStaticMesh(W_Model))
	{
		// If W_Model is properly Cast and an associated StaticMesh with collisions exists
		W_ModelStaticMeshComponent->SetSimulatePhysics(W_ModelStaticMeshComponent->CanEditSimulatePhysics());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to assign associated W_Model to Static Mesh Component."));
	}
}

// Called when the game starts or when spawned
void ASnowfallItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnowfallItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnowfallItem::Interact(AActor* InteractingActor)
{
	UE_LOG(LogTemp, Display, TEXT("Interacted with thing."));
}

