// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SnowfallCharacter.h"
#include "GameFramework/PlayerController.h"
#include "SnowfallCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class SNOWFALL_API ASnowfallCharacterController : public APlayerController
{
	GENERATED_BODY()

private:

	ASnowfallCharacter* controlledCharacter;
	UWeaponBase* activeWeapon;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginPlayingState() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
