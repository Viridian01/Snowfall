// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "SnowfallItem.generated.h"

UCLASS()
class SNOWFALL_API ASnowfallItem : public AActor, public IInteractable
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* W_Model;

	UStaticMeshComponent* W_ModelStaticMeshComponent;
	
public:	
	// Sets default values for this actor's properties
	ASnowfallItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Name;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* InteractingActor) override;

};
